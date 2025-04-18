//https://www.spoj.com/problems/MAXCHILDSUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int B = 450;

vector<int> adj[N];

int val[N];
int sz[N];
int parent[N];
int up[N];
int tin[N];
long long heavy_sum[N];
long long heavy_ans[N];

int timer = 0;

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void dfs(int u) {
    tin[u] = timer++;
    sz[u] = 1;
    if (u != 0 && adj[parent[u]].size() > B) {
        up[u] = u;
    } else {
        up[u] = up[parent[u]];
    }
    for (int v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];

    }

}

int main() {
    IOS;
    int q, n = 1;
    cin >> q;
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, v;
            cin >> p >> v;
            p--;
            val[n] = v;
            adj[p].push_back(n);
            parent[n] = p;
            queries.push_back(make_pair(1, n));
            n++;
        } else {
            int u;
            cin >> u;
            u--;
            queries.push_back(make_pair(2, u));
        }
    }
    up[0] = -1;
    dfs(0);
    BIT bit(n);
    for (int i = 0; i < q; i++) {
        auto [t, u] = queries[i];
        if (t == 1) {
            bit.upd(tin[u] + 1, val[u]);
            int v = u;
            while (1) {
                if (up[v] == -1) {
                    break;
                }
                v = up[v];
                heavy_sum[v] += val[u];
                heavy_ans[parent[v]] = max(heavy_ans[parent[v]], heavy_sum[v]);
                v = parent[v];
            }
        } else {
            if (adj[u].size() < B) {
                long long best = 0;
                for (int v : adj[u]) {
                    best = max(best, bit.query(tin[v] + 1, tin[v] + sz[v]));
                }
                cout << best << endl;
            } else {
                cout << heavy_ans[u] << endl;
            }
        }
    }
    return 0;
}
