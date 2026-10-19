//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e18;
const int ADD = 1e4;

struct MCMF {
    struct Edge {
        int from, to;
        ll cap, f, cost;
    };
    int n, s, t, m;

    vector<vector<int>> adj;
    vector<int> ptr;
    vector<ll> dist;
    vector<int> vis;
    vector<Edge> edges;

    MCMF(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        m = 0;
        adj.resize(n);
        ptr.resize(n);
        dist.resize(n);
        vis.resize(n);
    }

    void add_edge(int u, int v, ll cap, ll cost) {
        adj[u].push_back(m);
        edges.push_back({u, v, cap, 0, cost});
        m++;
        adj[v].push_back(m);
        edges.push_back({v, u, cap, cap, -cost});
        m++;
    }

    int spfa() {
        vector<int> inq(n, 0);
        fill(dist.begin(), dist.end(), INF);
        dist[s] = 0;
        inq[s] = 1;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for (int e : adj[u]) {
                auto [_, v, cap, f, cost] = edges[e];
                if (cap - f > 0 && dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    if (!inq[v]) {
                        inq[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dist[t] != INF;
    }

    ll dfs(int u, ll pushed) {
        if (!pushed) {
            return 0;
        }
        if (u == t) {
            return pushed;
        }
        vis[u] = 1;
        for (int &i = ptr[u]; i < adj[u].size(); i++) {
            int e = adj[u][i];
            auto [_, v, cap, f, cost] = edges[e];
            if (cap - f == 0 || dist[v] != dist[u] + cost || vis[v]) {
                continue;
            }
            ll cur = dfs(v, min(pushed, cap - f));
            if (!cur) {
                continue;
            }
            pushed = cur;
            edges[e].f += pushed;
            edges[e ^ 1].f -= pushed;
            vis[u] = 0;
            return pushed;
        }
        vis[u] = 0;
        return 0;
    }

    ll flow(ll k) {
        ll ans = 0, f = 0;
        while (spfa() && f < k) {
            fill(ptr.begin(), ptr.end(), 0);
            while (1) {
                ll cur = dfs(s, INF);
                if (!cur) {
                    break;
                }
                ans += dist[t] * cur;
                f += cur;
            }
        }
        return ans;
    }
};

int main() {
    IOS;
    int n;
    cin >> n;
    vector<vector<vector<ll>>> cubes;
    vector<pair<int, int>> pairs{{0, 4}, {1, 3}, {2, 5}};
    for (int i = 0; i < n; i++) {
        vector<int> cur(6, 0);
        for (int j = 0; j < 6; j++) {
            cin >> cur[j];
        }
        cubes.push_back(vector<vector<ll>>(7, vector<ll>(7, INF)));;
        for (int mask = 0; mask < 64; mask++) {
            ll s = 0;
            for (int j = 0; j < 6; j++) {
                int c = mask & (1 << j);
                if (c) {
                    s += cur[j];
                }
            }
            int al = 0, pr = 0;
            for (auto [x, y] : pairs) {
                int cx = min(1, mask & (1 << x));
                int cy = min(1, mask & (1 << y));
                if (cx && cy) {
                    pr++;
                } else if (cx || cy) {
                    al++;
                }
            }
            cubes[i][pr][al] = min(cubes[i][pr][al], s);
        }
    }
    ll ans = INF;
    for (int x = 1; x <= n; x++) {
        if (n % x != 0) {
            continue;
        }
        for (int y = x; y <= n / x; y++) {
            if ((n / x) % y != 0) {
                continue;
            }
            int z = n / x / y;
            if (z < y) {
                continue;
            }
            vector<vector<ll>> cap(7, vector<ll>(7, 0));
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    for (int k = 0; k < z; k++) {
                        int pr = 0, al = 0;
                        int cx = (i == 0) + (i == x - 1);
                        if (cx == 1) {
                            al++;
                        } else if (cx == 2) {
                            pr++;
                        }
                        int cy = (j == 0) + (j == y - 1);
                        if (cy == 1) {
                            al++;
                        } else if (cy == 2) {
                            pr++;
                        }
                        int cz = (k == 0) + (k == z - 1);
                        if (cz == 1) {
                            al++;
                        } else if (cz == 2) {
                            pr++;
                        }
                        cap[pr][al]++;
                    }
                }
            }
            MCMF mcmf = MCMF(1 + n + 49 + 1, 0, 1 + n + 49);
            for (int i = 0; i < n; i++) {
                mcmf.add_edge(0, 1 + i, 1, 0);
                for (int j = 0; j <= 6; j++) {
                    for (int k = 0; k <= 6; k++) {
                        ll cost = cubes[i][j][k];
                        if (cap[j][k] != 0) {
                            mcmf.add_edge(1 + i, 1 + n + j * 7 + k, 1, cost);
                        }
                    }
                }
            }
            for (int i = 0; i <= 6; i++) {
                for (int j = 0; j <= 6; j++) {
                    if (cap[i][j] != 0) {
                        mcmf.add_edge(1 + n + i * 7 + j, 1 + n + 49, cap[i][j], 0);
                    }
                }
            }
            ans = min(ans, mcmf.flow(n));
        }
    }
    cout << ans;


    return 0;
}
