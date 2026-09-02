//https://codeforces.com/contest/1254/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 500;
const ll M = 998244353;

vector<int> adj[N];
int tin[N];
int tout[N];
int pos[N];
int sz[N];
ll sum[N];
ll add[N];

int euler = 0;
int timer = 0;

ll inv;

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

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        l++, r++;
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        i++;
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
};

void dfs(int u, int p) {
    pos[u] = euler++;
    sz[u] = 1;
    tin[u] = timer++;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    sort(adj[u].begin(), adj[u].end(), [&](int x, int y) { return tin[x] < tin[y];});
    tout[u] = timer++;
}

void redfs(int u, int p, ll s) {
    sum[u] += s;
    for (int v : adj[u]) {
        if (v != p) {
            redfs(v, u, (s + add[u] * (sz[u] - sz[v]) % M * inv % M) % M);
        }
    }

    add[u] = 0;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    inv = modPow(n, M - 2);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    BIT bit(n);
    vector<pair<int, int>> buf;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, d;
            cin >> v >> d;
            v--;
            ll x = (ll)d * sz[v] % M * inv % M;
            bit.upd(0, n - 1, x);
            bit.upd(pos[v], pos[v] + sz[v] - 1, M - x);
            bit.upd(pos[v], pos[v], x);
            x = (ll)d * (n - sz[v]) % M * inv % M;
            bit.upd(pos[v], pos[v] + sz[v] - 1, x);

            buf.push_back({v, d});
            add[v] = (add[v] + d) % M;
        } else {
            int u;
            cin >> u;
            u--;
            ll ans = sum[u] + bit.query(pos[u]);
            for (auto [v, d] : buf) {
                if (u != v && is_ancestor(v, u)) {
                    auto it = upper_bound(adj[v].begin(), adj[v].end(), u, [&](int x, int u) { return tin[x] < tin[u];});
                    it--;
                    int anc = *it;
                    ans += (ll)d * (sz[v] - sz[anc]) % M * inv % M;
                }
            }
            cout << ans % M << endl;
        }
        if (buf.size() > SQ) {
            buf.clear();
            redfs(0, 0, 0);
        }
    }
    return 0;
}
