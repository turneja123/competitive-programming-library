//https://evaluator.hsin.hr/events/coci26_1/tasks/HONI252616harmonija/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 18;

const ll INF = 1e18;

struct Data {
    ll dp[5][5];

    Data(ll x, ll y) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                dp[i][j] = -INF;
            }
        }
        for (int i = 0; i < 5; i++) {
            if (i + 1 < 5) {
                dp[i][i + 1] = max(dp[i][i + 1], y);
            }
            if (i - 1 >= 0) {
                dp[i][i - 1] = max(dp[i][i - 1], x);
            }
        }

    }
    Data() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                dp[i][j] = -INF;
            }
        }
    }

};

Data combine(Data &left, Data& right) {
    Data node;
    for (int i = 0; i < 5; i++) {
        for (int k = 0; k < 5; k++) {
            for (int j = 0; j < 5; j++) {
                ll L = left.dp[i][j], R = right.dp[j][k];
                if (L == -INF || R == -INF) {
                    continue;
                }
                node.dp[i][k] = max(node.dp[i][k], L + R);
            }
        }
    }
    return node;
}

vector<int> adj[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;
int x[N], y[N];
int depth[N];

Data dat[K][N];
Data dat_rev[K][N];

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    dat[0][u] = Data(x[u], y[u]);
    dat_rev[0][u] = Data(x[u], y[u]);

    for (int k = 1; k < K; k++) {
        int v = up[k - 1][u];
        up[k][u] = up[k - 1][v];
        dat[k][u] = combine(dat[k - 1][u], dat[k - 1][v]);
        dat_rev[k][u] = combine(dat_rev[k - 1][v], dat_rev[k - 1][u]);
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

int kth(int u, int k) {
    for (int j = K - 1; k >= 0; k--) {
        int c = k - (1 << j);
        if (c >= 0) {
            u = up[j][u];
            k = c;
        }
    }
    return u;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i< n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i< n; i++) {
        cin >> y[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u == v) {
            cout << max(x[u], y[u]) << endl;
            continue;
        }
        int l = lca(u, v);
        ll ans = -INF;
        if (u == l) {
            Data cur = dat_rev[0][v];
            v = up[0][v];
            int k = depth[v] - depth[l];
            for (int j = K - 1; j >= 0; j--) {
                int c = k - (1 << j);
                if (c >= 0) {
                    cur = combine(dat_rev[j][v], cur);
                    v = up[j][v];
                    k = c;
                }
            }
            cur = combine(dat_rev[0][u], cur);

            for (int k = 0; k < 5; k++) {
                ans = max(ans, cur.dp[2][k]);
            }

        } else {
            Data cur = dat[0][u];
            u = up[0][u];
            int k = depth[u] - depth[l];
            for (int j = K - 1; j >= 0; j--) {
                int c = k - (1 << j);
                if (c >= 0) {
                    cur = combine(cur, dat[j][u]);
                    u = up[j][u];
                    k = c;
                }
            }
            cur = combine(cur, dat[0][l]);
            if (v != l) {
                Data cur2 = dat_rev[0][v];
                v = up[0][v];
                int k = depth[v] - depth[l];
                for (int j = K - 1; j >= 0; j--) {
                    int c = k - (1 << j);
                    if (c >= 0) {
                        cur2 = combine(dat_rev[j][v], cur2);
                        v = up[j][v];
                        k = c;
                    }
                }
                cur = combine(cur, cur2);
            }

            for (int k = 0; k < 5; k++) {
                ans = max(ans, cur.dp[2][k]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
