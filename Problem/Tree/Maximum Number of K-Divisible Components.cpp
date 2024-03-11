//https://leetcode.com/problems/maximum-number-of-k-divisible-components/
class Solution {
public:
    long long dfs(int u, vector<vector<int>>& adj, vector<int>& values, long long k, int parent, int *ans) {
        long long sum = values[u];
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = *it;
            if (v != parent) {
                sum += dfs(v, adj, values, k, u, ans);
            }
        }
        if (sum % k == 0) {
            (*ans)++;
            sum = 0;
        }
        return sum;
    }
    
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        int ans = 0;
        dfs(0, adj, values, (long long)k, -1, &ans);
        return ans;
    }
};