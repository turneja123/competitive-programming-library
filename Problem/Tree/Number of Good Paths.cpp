//https://leetcode.com/problems/number-of-good-paths/description/
class Solution {
public:
    int color[30005];
    long long ans[30005];
    int sz[30005];
    int parent[30005];
    vector<int> adj[30005];
    map<int, long long> mp[30005];
    long long add = 0;

    int dsu_find(int p) {
        if (parent[p] == p) {
            return p;
        }
        parent[p] = dsu_find(parent[p]);
        return parent[p];
    }

    void dsu_merge(int a, int b, int lim) {
        while (mp[a].size() && (mp[a].begin())->first < lim) {
            mp[a].erase(mp[a].begin());
        }
        while (mp[b].size() && (mp[b].begin())->first < lim) {
            mp[b].erase(mp[b].begin());
        }
        if (mp[a].size() > mp[b].size()) {
            swap(a, b);
        }
        parent[a] = b;
        for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
            int x = it->first;
            if (mp[b].find(x) != mp[b].end()) {
                add += mp[b][x] * it->second;
                mp[b][x] += it->second;
            } else {
                mp[b][x] = it->second;
            }
        }
        return;
    }

    void dfs(int u, int p) {
        vector<int> child;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                child.push_back(v);
            }
        }
        for (int v : child) {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                dsu_merge(a, b, color[u]);
            }
        }
        ans[u] = add;
        add = 0;
        return;
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        for (int i = 0; i < n - 1; i++) {
            int u = edges[i][0], v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
            color[i] = vals[i];
            mp[i][color[i]] = 1;
        }
        dfs(0, -1);
        long long total = 0;
        for (int i = 0; i < n; i++) {
            total += ans[i];
        }
        return total + n;
    }
};