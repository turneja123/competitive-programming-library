//https://ocpc2026w.eolymp.space/en/compete/ig3v7lohgt0vd43nv48bk2lb4o/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;
const ll M = 998244353;

ll dp[N][3];
vector<int> adj[N];

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

void ntt(vector<ll> &a, int typ) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	vector<int> rev(n);
	for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	}
	for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
	}
	int g = modPow(3, (M - 1) / n);
	vector<ll> wn(n), w(n);
	wn[0] = 1;
	for (int i = 1; i < n; i++) {
        wn[i] = wn[i - 1] * g % M;
	}
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0, t = n / (2 * k); i < k; i++) {
            w[i] = wn[i * t];
        }
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll x = a[i + j], y = a[i + j + k] * w[j] % M;
                a[i + j] = x + y - (x + y >= M ? M : 0);
                a[i + j + k] = x - y + (x - y < 0 ? M : 0);
            }
        }
    }
    if (!typ) {
        reverse(a.begin() + 1, a.end());
        ll inv_n = modPow(n, M - 2);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * inv_n % M;
        }
    }
}

vector<ll> convMod(vector<ll> a, vector<ll> b) {
    int m = a.size() + b.size() - 1;
    if (m == 1) {
        return {a[0] * b[0] % M};
    }
	int B = 32 - __builtin_clz(m - 1);
	int n = 1 << B;

    a.resize(n), b.resize(n);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * b[i] % M;
    }
    ntt(a, 0);
    a.resize(m);
    return a;
}

vector<long long> calc(int l, int r, int k, vector<pair<ll, ll>> &polys) {
    if (l == r) {
        vector<long long> ans = {polys[l].first, polys[l].second};
        return ans;
    }
    int mid = (l + r) / 2;
    vector<long long> a = calc(l, mid, k, polys), b = calc(mid + 1, r, k, polys);
    vector<long long> ans = convMod(a, b);
    ans.resize(min(k + 1, r - l + 2));
    return ans;
}


void dfs(int u, int p, int k) {
    dp[u][0] = 1;
    vector<pair<ll, ll>> polys;
    int j = 0, n = adj[u].size();
    if (u != 0) {
        n--;
    }
    vector<ll> pref(n, 0), suf(n, 0);
    vector<int> c;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, k);
            c.push_back(v);
            pref[j] = (j == 0 ? 1 : pref[j - 1]) * (dp[v][0] + dp[v][1]) % M;
            j++;
        }
    }
    for (int j = n - 1; j >= 0; j--) {
        int v = c[j];
        suf[j] = (j == n - 1 ? 1 : suf[j + 1]) * (dp[v][0] + dp[v][1]) % M;
    }
    j = 0;
    for (int v : adj[u]) {
        if (v != p) {
            ll prod = (j == 0 ? 1 : pref[j - 1]) * (j == n - 1 ? 1 : suf[j + 1]) % M;
            dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]) % M;
            dp[u][1] = (dp[u][1] + dp[v][2] * prod % M) % M;
            polys.push_back({(dp[v][0] + dp[v][1]) % M, dp[v][0]});
            j++;
        }
    }
    if (polys.size() >= k - 1) {
        vector<ll> ans = calc(0, polys.size() - 1, k, polys);
        dp[u][2] = ans[k - 1];
        if (ans.size() > k) {
            dp[u][1] = (dp[u][1] + ans[k]) % M;
        }
    }
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0, k);
    cout << (dp[0][0] + dp[0][1] - 1 + M) % M;



    return 0;
}
