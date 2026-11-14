//https://codeforces.com/contest/2279/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

int deg[N];
int pref[N];
int terminal[N];
vector<int> adj[N];
vector<pair<int, int>> adj_ed[N];

vector<int> bfs(int n, int s) {
    vector<int> dist(n, INF);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int w, x, y, z;
        cin >> w >> x >> y >> z;
        w--, x--, y--, z--;
        vector<pair<int, int>> edge_nodes;


        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;

        }
        for (int i = 0; i < n; i++) {
            sort(adj[i].begin(), adj[i].end());
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + deg[i];
        }

        auto idx = [&](int u, int v) -> int {
            int c = (u == 0 ? 0 : pref[u - 1]);
            int ptr = lower_bound(adj[u].begin(), adj[u].end(), v) - adj[u].begin();
            return n + c + ptr;

        };

        int id = n;
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                if (i == y) {
                    terminal[id] = j + 1;
                }
                edge_nodes.push_back({i, j});
                adj_ed[id].push_back({i, 0});
                adj_ed[i].push_back({id, 2});
                adj_ed[id].push_back({idx(j, i), 1});
                id++;
            }
        }
        vector<int> distx = bfs(n, x);
        vector<int> distz = bfs(n, z);


        priority_queue<pair<int, int>> pq;
        vector<int> dist(id, INF);
        for (int k : adj[w]) {
            int u = idx(w, k);
            dist[u] = distx[k];
            pq.push({-dist[u], u});
        }
        int ans = INF;
        if (w == y) {
            ans = distx[z];
        }
        while (pq.size()) {
            auto [d, u] = pq.top();
            d = -d;
            pq.pop();
            if (dist[u] != d) {
                continue;
            }
            if (terminal[u]) {
                ans = min(ans, d + distz[terminal[u] - 1]);
            }
            for (auto [v, c] : adj_ed[u]) {
                if (dist[v] > c + d) {
                    dist[v] = c + d;
                    pq.push({-dist[v], v});
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < id; i++) {
            adj[i].clear();
            adj_ed[i].clear();
            deg[i] = 0;
            terminal[i] = 0;
        }

    }

    return 0;
}
