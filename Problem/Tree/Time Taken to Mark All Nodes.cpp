//https://leetcode.com/contest/biweekly-contest-136/problems/time-taken-to-mark-all-nodes/
const int N = 1e5 + 5;
vector<int> adj[N];
int depth[N];
int subtree[N];
int dp[N];

class Solution {
public:
    void dfs_subtree(int u, int p) {
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 2 - v % 2;
                dfs_subtree(v, u);
                subtree[u] = max(subtree[u], subtree[v] + 2 - v % 2);
            }
        }
    }

    void dfs(int u, int p) {
        multiset<int> st[2];
        for (int v : adj[u]) {
            if (v != p) {
                st[v % 2].insert(subtree[v]);
            }
        }
        for (int v : adj[u]) {
            if (v != p) {
                st[v % 2].erase(st[v % 2].find(subtree[v]));
                dp[v] = dp[u] + 2 - u % 2;
                if (st[0].size()) {
                    dp[v] = max(dp[v], *st[0].rbegin() + 2 - u % 2 + 2);
                }
                if (st[1].size()) {
                    dp[v] = max(dp[v], *st[1].rbegin() + 2 - u % 2 + 1);
                }
                st[v % 2].insert(subtree[v]);
                dfs(v, u);
            }
        }
    }

    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        dfs_subtree(0, 0);
        dfs(0, 0);
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            ans[i] = max(subtree[i], dp[i]);
            depth[i] = 0, subtree[i] = 0, dp[i] = 0;
            adj[i].clear();
        }
        return ans;
    }
};
