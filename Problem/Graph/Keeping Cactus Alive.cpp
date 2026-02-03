//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 2e9 + 5;

struct Edge {
    int u;
    int v;
    int wt;
};

int parent[N];
int parent_ed[N];
Edge edges[N];

int on_cyc[N];
int vis[N];
int vis_ed[N];

vector<tuple<int, int, int>> adj[N];
vector<vector<int>> cycles;

void dfs(int u, int ed) {
    vis[u] = 1;
    for (auto [v, wt, e] : adj[u]) {
        if (vis_ed[e]) {
            continue;
        }
        vis_ed[e] = 1;

        if (!vis[v]) {
            parent[v] = u;
            parent_ed[v] = e;
            dfs(v, e);
        } else if (e != ed) {
            vector<int> cyc{e};
            int x = u;
            while (x != v) {
                cyc.push_back(parent_ed[x]);
                x = parent[x];
            }
            for (int j : cyc) {
                on_cyc[j] = 1;
            }
            cycles.push_back(cyc);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back({v, wt, i});
            adj[v].push_back({u, wt, i});
            edges[i] = {u, v, wt};
            on_cyc[i] = 0;
            vis_ed[i] = 0;
        }
        dfs(0, -1);
        int ans = INF;
        for (int i = 0; i < m; i++) {
            if (!on_cyc[i]) {
                ans = min(ans, edges[i].wt);
            }
        }
        for (auto &v : cycles) {
            sort(v.begin(), v.end(), [&](int a, int b) {return edges[a].wt < edges[b].wt;});
            ans = min(ans, edges[v[0]].wt + edges[v[1]].wt);
            if (v.size() > 2) {
                ans = min(ans, edges[v[2]].wt);
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = 0;
        }
        cycles.clear();

    }
    return 0;
}
