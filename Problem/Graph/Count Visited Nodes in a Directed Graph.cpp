//https://leetcode.com/contest/weekly-contest-365/problems/count-visited-nodes-in-a-directed-graph/
class Solution {
public:
    vector<int> adj[100005];
    vector<int> cycle;
    int color[100005];
    int parent[100005];
    bool vis[100005];
    bool cyc[100005];

    void dfs(int u, int p, vector<int> &dist) {
        color[u] = 1;
        parent[u] = p;
        for (int v : adj[u]) {
            if (color[v] == 0) {
                dfs(v, u, dist);
            } else if (color[v] == 1) {
                int x = u;
                while (x != v) {
                    cycle.push_back(x);
                    cyc[x] = true;
                    x = parent[x];
                }
                cyc[v] = true;
                cycle.push_back(v);
                for (int x : cycle) {
                    dist[x] = cycle.size();
                }
                cycle.clear();
            }
            if (!cyc[u]) {
                dist[u] += dist[v];
            }
        }
        color[u] = 2;
        return;
    }

    vector<int> countVisitedNodes(vector<int>& edges) {
        int n = edges.size();
        for (int i = 0; i < n; i++) {
            adj[i].push_back(edges[i]);
        }
        vector<int> dist(n, 1);
        for (int i = 0; i < n && cycle.size() == 0; i++) {
            if (!color[i]) {
                dfs(i, i, dist);
            }
        }
        return dist;

    }
};
