//https://codeforces.com/contest/2229/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

vector<int> adj[N];
int mx[N];

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            mx[u] = max({mx[u], mx[v], v});
        }
    }
}

struct BIT {
    int n;
    vector<ll> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, ll val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] = (t[i] + val) % M;
        }
    }
    ll query(int i) {
        ll ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans % M;
    }
    ll query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return (query(r) - query(l - 1) + M) % M;
    }
};


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            mx[i] = 0;
        }

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        if (adj[n].size() == 1) {
            cout << 1 << endl;
            continue;
        }
        dfs(n, n);

        int x = -1;
        for (int v : adj[n]) {
            if (!(v == n - 1 || mx[v] == n - 1)) {
                x = max({x, v, mx[v]});
            }
        }
        int y = -1;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() == 1) {
                y = i;
            }
        }
        BIT bit(n);
        bit.upd(y, 1);

        for (int i = y + 1; i < n; i++) {
            if (mx[i] < i) {
                ll ct = bit.query(mx[i] + 1, i);
                bit.upd(i, ct);
            }
        }
        cout << bit.query(x + 1, n - 1) << endl;

    }

    return 0;
}
