//https://eolymp.com/en/problems/12309
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 20;
const int N = 1e6 + 5;

struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU() {}

    DSU(int n) {
        parent.resize(n);
        sz.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }
        return parent[a] = dsu_find(parent[a]);
    }

    void dsu_unite(int a, int b) {
        if (sz[b] > sz[a]) {
            swap(a, b);
        }
        sz[a] += sz[b];
        parent[b] = a;
    }
};

int ans[N];
int color[N];


void calc(int a, int b, int k, vector<DSU> &dsu) {
    int A = dsu[k].dsu_find(a), B = dsu[k].dsu_find(b);
    if (A != B) {
        dsu[k].dsu_unite(A, B);
        if (k != 0) {
            k--;
            calc(a, b + (1 << k), k, dsu);
            calc(a + (1 << k), b, k, dsu);
        }
    }
    return;
}

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

ll pw_p[N], pw_q[N];
ll inv_p[N], inv_q[N];

pair<ll, ll> pref[N], suf[N];

pair<ll, ll> get_pref(int l, int r, int n) {
    pair<ll, ll> ans = pref[r];
    if (l != 0) {
        ans.first = (ans.first - pref[l - 1].first + M) * inv_p[l] % M;
        ans.second = (ans.second - pref[l - 1].second + M) * inv_q[l] % M;
    }
    return ans;
}

pair<ll, ll> get_suf(int l, int r, int n) {
    pair<ll, ll> ans = suf[l];
    if (r != n - 1) {
        ans.first = (ans.first - suf[r + 1].first + M) * inv_p[n - 1 - r] % M;
        ans.second = (ans.second - suf[r + 1].second + M) * inv_q[n - 1 - r] % M;
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<DSU> dsu(K);
        for (int i = 0; i < K; i++) {
            dsu[i] = DSU(n);
        }
        vector<pair<int, int>> x, y;

        for (int i = 0; i < q; i++) {
            int l, r, t;
            cin >> l >> r >> t;
            l--, r--;
            if (t == 0) {
                y.push_back({l + 1, r});
            } else {
                x.push_back({l + 1, r});
            }
        }
        for (auto [l, r] : x) {
            if (l >= r) {
                continue;
            }
            int d = (r - l + 1) / 2;
            int a = l, b = l + d + (r - l + 1) % 2;
            int k = 31 - __builtin_clz(d);
            calc(a, b + d - (1 << k), k, dsu);
            calc(a + d - (1 << k), b, k, dsu);
        }

        for (int i = 0, j = 1; i < n; i++) {
            int a = dsu[0].dsu_find(i);
            if (color[a] != 0) {
                ans[i] = color[a];
                continue;
            }
            color[a] = j++;
            ans[i] = color[a];
        }
        pw_p[0] = 1, pw_q[0] = 1;
        inv_p[0] = 1, inv_q[0] = 1;
        for (int i = 1; i < n; i++) {
            pw_p[i] = pw_p[i - 1] * P % M;
            pw_q[i] = pw_q[i - 1] * Q % M;
            inv_p[i] = inv_p[i - 1] * INV_P % M;
            inv_q[i] = inv_q[i - 1] * INV_Q % M;
        }
        for (int i = 0; i < n; i++) {
            pref[i].first = ((i == 0 ? 0 : pref[i - 1].first) + ans[i] * pw_p[i]) % M;
            pref[i].second = ((i == 0 ? 0 : pref[i - 1].second) + ans[i] * pw_q[i]) % M;
        }
        for (int i = n - 1; i >= 0; i--) {
            suf[i].first = ((i == n - 1 ? 0 : suf[i + 1].first) + ans[i] * pw_p[n - 1 - i]) % M;
            suf[i].second = ((i == n - 1 ? 0 : suf[i + 1].second) + ans[i] * pw_q[n - 1 - i]) % M;
        }
        int can = 1;
        for (auto [l, r] : y) {
            if (r - l <= 0 || get_pref(l, r, n) == get_suf(l, r, n)) {
                can = 0;
            }
        }
        if (!can) {
            cout << -1 << endl;
        } else {
            ll last = 1;
            cout << last << " ";
            for (int i = 1; i < n; i++) {
                last += ans[i];
                cout << last << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < n; i++) {
            color[i] = 0;
            ans[i] = 0;
        }

    }
    return 0;
}
