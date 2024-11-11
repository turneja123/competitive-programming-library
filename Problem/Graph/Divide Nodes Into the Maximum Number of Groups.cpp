//https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/
const int N = 505;
class Solution {
public:
    vector<int> comp;
    vector<int> adj[N];
    bool vis[N];
    int depth[N];
    void dfs(int u) {
        vis[u] = true;
        comp.push_back(u);
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs(v);
            }
        }
    }

    int calc(int u) {
        int m = comp.size();
        for (int i = 0; i < m; i++) {
            depth[comp[i]] = N;
        }
        depth[u] = 1;
        queue<int> q;
        q.push(u);
        int ans = 1;
        while (q.size()) {
            int u = q.front();
            q.pop();
            ans = max(ans, depth[u]);
            for (int v : adj[u]) {
                if (depth[v] + 1 < depth[u] || depth[v] == depth[u]) {
                    return -1;
                }
                if (depth[v] > depth[u] + 1) {
                    depth[v] = depth[u] + 1;
                    q.push(v);
                }
            }
        }
        return ans;
    }

    int magnificentSets(int n, vector<vector<int>>& edges) {
        for (int i = 0; i < edges.size(); i++) {
            edges[i][0]--, edges[i][1]--;
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
                int cur = -1;
                for (int u : comp) {
                    cur = max(cur, calc(u));
                }
                if (cur == -1) {
                    return -1;
                }
                comp.clear();
                ans += cur;
            }
        }
        return ans;
    }
};
