//https://leetcode.com/problems/valid-arrangement-of-pairs
const int N = 1e5 + 5;
class Solution {
public:
    vector<int> adj[N];
    map<int, int> mp;
    int val[N];
    int in_deg[N];
    int out_deg[N];
    vector<int> x;
    void dfs(int u) {
        while (adj[u].size()) {
            int v = adj[u].back();
            adj[u].pop_back();
            dfs(v);
        }
        x.push_back(u);
        return;
    }

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int m = pairs.size();
        for (int i = 0; i < m; i++) {
            int u = pairs[i][0], v = pairs[i][1];
            auto it = mp.find(u);
            if (it == mp.end()) {
                val[mp.size()] = u;
                mp[u] = mp.size();
                u = mp.size() - 1;
            } else {
                u = mp[u];
            }
            it = mp.find(v);
            if (it == mp.end()) {
                val[mp.size()] = v;
                mp[v] = mp.size();
                v = mp.size() - 1;
            } else {
                v = mp[v];
            }
            adj[u].push_back(v);
            in_deg[v]++;
            out_deg[u]++;
        }
        int n = mp.size();
        int st = 0;
        for (int i = 0; i < n; i++) {
            if (out_deg[i] == in_deg[i] + 1) {
                st = i;
            }
        }
        dfs(st);
        vector<vector<int>> ans;
        reverse(x.begin(), x.end());
        for (int i = 0; i < x.size() - 1; i++) {
            ans.push_back({val[x[i]], val[x[i + 1]]});
        }
        return ans;

    }
};
