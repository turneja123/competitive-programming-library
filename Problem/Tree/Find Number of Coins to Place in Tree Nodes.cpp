//https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/description/
class Solution {
public:
    vector<int> adj[20005];
    long long val[20005];
    int parent[20005];
    int sz[20005];
    multiset<long long> st[20005];
    
    int dsu_find(int p) {
        if (parent[p] == p) {
            return p;
        }
        parent[p] = dsu_find(parent[p]);
        return parent[p];
    }

    void dsu_merge(int a, int b) {
        if (st[a].size() > st[b].size()) {
            swap(a, b);
        }
        parent[a] = b;
        for (auto it = st[a].begin(); it != st[a].end(); ++it) {
            st[b].insert(*it);
        }
        return;
    }
    
    void dfs(int u, int p, vector<long long> &ans) {
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, ans);
            }
        }
        for (int v : adj[u]) {
            if (v != p) {
                int a = dsu_find(u), b = dsu_find(v);
                if (a != b) {
                    dsu_merge(a, b);
                }
            }
        }
        int d = dsu_find(u);
        if (st[d].size() < 3) {
            ans[u] = 1;
        } else {
            auto it = st[d].begin();
            long long prodl = *it;
            ++it;
            prodl *= *it;
            auto it2 = st[d].rbegin();
            prodl *= *it2;
            long long prodr = *it2;
            ++it2;
            prodr *= *it2;
            ++it2;
            prodr *= *it2;
            ans[u] = max({(long long)0, prodl, prodr});
        }
    }
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        for (int i = 0; i < n - 1; i++) {
            int u = edges[i][0], v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            val[i] = cost[i];
            sz[i] = 1;
            parent[i] = i;
            st[i].insert(val[i]);
        }
        vector<long long> ans(n, 0);
        dfs(0, 0, ans);
        return ans;
    }
};