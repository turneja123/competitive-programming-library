//https://leetcode.com/problems/sum-of-distances-in-tree/description/
class Solution {
public:
    void dfs_sub(int u, int p, vector<int> &sz, vector<int> &subtree, vector<vector<int>> &adj) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs_sub(v, u, sz, subtree, adj);
                sz[u] += sz[v];
                subtree[u] += subtree[v] + sz[v];
            }
        }
    }
    void dfs_parent(int u, int p, vector<int> &sz, vector<int> &subtree, vector<int> &parent, vector<vector<int>> &adj, int n) {
        if (p != -1) {
            parent[u] += subtree[p] - subtree[u] - 2 * sz[u] + sz[p];
            parent[u] += parent[p] + n - sz[p];
        }
        for (int v : adj[u]) {
            if (v != p) {
                dfs_parent(v, u, sz, subtree, parent, adj, n);
            }
        }
    }

    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < edges.size(); i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        vector<int> sz(n, 0);
        vector<int> subtree(n, 0);
        dfs_sub(0, -1, sz, subtree, adj);
        vector<int> parent(n, 0);
        dfs_parent(0, -1, sz, subtree, parent, adj, n);
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            ans[i] = parent[i] + subtree[i];
        }
        return ans;
    }
};