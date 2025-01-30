//https://leetcode.com/contest/weekly-contest-432/problems/minimize-the-maximum-edge-weight-of-graph/
const int N = 1e5 + 5;
vector<int> adj[N];
bool vis[N];
class Solution {
public:
    void dfs(int u) {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs(v);
            }
        }
        return;
    }

    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        int l = 1, r = 1e6, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            for (int i = 0; i < edges.size(); i++) {
                if (edges[i][2] <= mid) {
                    adj[edges[i][1]].push_back(edges[i][0]);
                }
            }
            dfs(0);
            bool can = true;
            for (int i = 0; i < n; i++) {
                adj[i].clear();
                if (!vis[i]) {
                    can = false;
                } else {
                    vis[i] = false;
                }
            }
            if (can) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
