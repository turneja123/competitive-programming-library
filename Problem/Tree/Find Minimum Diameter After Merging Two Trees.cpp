//https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
class Solution {
public:
    vector<int> adj[200005];
    int center_deg[200005];
    bool vis[200005];

    int mx, node;

    void dfs(int u, int p, int d) {
        for (int v : adj[u]) {
            if (v != p) {
                if (d + 1 > mx) {
                    mx = d + 1;
                    node = v;
                }
                dfs(v, u, d + 1);
            }
        }
        return;
    }

    vector<int> find_center(int n, int start) {
        vector<int> leaves;
        if (n == 1) {
            leaves.push_back(start);
            return leaves;
        }
        int ct = n;
        for (int i = start; i < n + start; i++) {
            if (center_deg[i] == 1) {
                leaves.push_back(i);
                vis[i] = true;
                ct--;
            }
        }
        while (ct > 0) {
            vector<int> nxt;
            for (int u : leaves) {
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        center_deg[v]--;
                        if (center_deg[v] == 1) {
                            nxt.push_back(v);
                            vis[v] = true;
                            ct--;
                        }
                    }
                }
            }
            leaves = nxt;
        }
        return leaves;
    }

    void diameter() {
        mx = 0;
        dfs(0, -1, 0);
        mx = 0;
        dfs(node, -1, 0);
    }

    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        for (int i = 0; i < n - 1; i++) {
            adj[edges1[i][0]].push_back(edges1[i][1]);
            adj[edges1[i][1]].push_back(edges1[i][0]);
        }
        for (int i = 0; i < m - 1; i++) {
            adj[edges2[i][0] + n].push_back(edges2[i][1] + n);
            adj[edges2[i][1] + n].push_back(edges2[i][0] + n);
        }
        for (int i = 0; i < n + m; i++) {
            center_deg[i] = adj[i].size();
        }
        vector<int> center_a = find_center(n, 0);
        vector<int> center_b = find_center(m, n);
        int ans = 0;
        for (int u : center_a) {
            for (int v : center_b) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                diameter();
                ans = max(ans, mx);
                adj[u].pop_back();
                adj[v].pop_back();
            }
        }
        return ans;
    }
};
