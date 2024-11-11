//https://leetcode.com/contest/biweekly-contest-113/problems/minimum-edge-reversals-so-every-node-is-reachable/
const int N = 1e5 + 5;
vector<pair<int, int>> adj[N];
int subtree[N];
int dp[N];

class Solution {
public:
    void dfs_subtree(int u, int p) {
        for (pair<int, int> pr : adj[u]) {
            int v = pr.first;
            if (v != p) {
                dfs_subtree(v, u);
                subtree[u] += subtree[v] + (pr.second == -1);
            }
        }

    }

    void dfs(int u, int p) {
        for (pair<int, int> pr : adj[u]) {
            int v = pr.first;
            if (v != p) {
                dp[v] += dp[u] + (pr.second == 1) + subtree[u] - subtree[v] - (pr.second == -1);
                dfs(v, u);
            }
        }
    }


    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], 1));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], -1));
        }
        dfs_subtree(0, 0);
        dfs(0, 0);
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = subtree[i] + dp[i];
            subtree[i] = 0, dp[i] = 0;
            adj[i].clear();
        }
        return ans;
    }
};
