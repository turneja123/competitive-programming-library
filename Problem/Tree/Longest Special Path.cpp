//https://leetcode.com/contest/biweekly-contest-148/problems/longest-special-path/
const int N = 5e4 + 5;
vector<pair<int, int>> adj[N];
multiset<int> st[N];
class Solution {
public:
    vector<vector<int>> up;
    int timer = 0, lg;
    int path[N];
    int depth[N];
    int mx[N];
    void dfs(int u, int p, vector<int> &nums) {
        if (st[nums[u]].size()) {
            mx[u] = max(mx[u], *st[nums[u]].rbegin() + 1);
        }
        st[nums[u]].insert(depth[u]);
        up[u][0] = p;
        for (int i = 1; i <= lg; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto [v, wt] : adj[u]) {
            if (v != p) {
                path[v] = path[u] + wt;
                mx[v] = mx[u];
                depth[v] = depth[u] + 1;
                dfs(v, u, nums);
            }
        }
        st[nums[u]].erase(st[nums[u]].find(depth[u]));
    }

    int kth(int v, int k) {
        while (k > 0) {
            int l = log2(k);
            v = up[v][l];
            k ^= 1 << l;
        }
        return v;
    }

    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adj[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
        }
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        dfs(0, 0, nums);
        vector<int> ans{0, N};
        for (int i = 0; i < n; i++) {
            int x = depth[i], y = mx[i];
            int v = kth(i, x - y);
            if (ans[0] < path[i] - path[v]) {
                ans[0] = path[i] - path[v];
                ans[1] = x - y + 1;
            } else if (ans[0] == path[i] - path[v]) {
                ans[1] = min(ans[1], x - y + 1);
            }
            adj[i].clear();
        }
        return ans;
    }
};
