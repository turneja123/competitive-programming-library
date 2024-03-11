//https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/
class Solution {
public:
    void dfs(int u, int p, int *timer, int lg, vector<int> &tin, vector<int> &tout, 
    vector<vector<int>> &up, vector<vector<pair<int, int>>> &adj, vector<vector<int>> &weights, vector<int> &depth) {
        tin[u] = ++(*timer);
        up[u][0] = p;
        depth[u] = depth[p] + 1;
        for (int i = 1; i <= lg; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = it->first, wt = it->second;
            if (v != p) {
                weights[u][wt]++;
                for (int i = 0; i < 30; i++) {
                    weights[v][i] += weights[u][i];
                }
                dfs(v, u, timer, lg, tin, tout, up, adj, weights, depth);
                weights[u][wt]--;
            } 
        }
        tout[u] = ++(*timer);
    }

    bool is_ancestor(int u, int v, vector<int> &tin, vector<int> &tout) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v, int lg, vector<int> &tin, vector<int> &tout, vector<vector<int>> &up) {
        if (is_ancestor(u, v, tin, tout)) {
            return u;
        }
        if (is_ancestor(v, u, tin, tout)) {
            return v;
        }
        for (int i = lg; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v, tin, tout)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, int>>> adj(n);
        vector<vector<int>> weights(n, vector<int>(30, 0));
         for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
        }
        vector<int> tin(n, 0);
        vector<int> tout(n, 0);
        vector<int> depth(n, 0);
        int lg = ceil(log2(n));
        vector<vector<int>> up(n, vector<int>(lg + 1, 0));
        int timer = 0;
        dfs(0, 0, &timer, lg, tin, tout, up, adj, weights, depth);
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            int u = queries[i][0], v = queries[i][1];
            int l = lca(queries[i][0], queries[i][1], lg, tin, tout, up);
            int ct = depth[u] + depth[v] - 2 * depth[l], diff = ct;
            for (int j = 0; j < 30; j++) {
                int edge = weights[u][j] + weights[v][j] - 2 * weights[l][j];
                diff = min(diff, ct - edge);
            }
            ans.push_back(diff);
        }
        return ans;
    }
};