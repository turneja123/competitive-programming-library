//https://leetcode.com/problems/find-edges-in-shortest-paths/description/
class Solution {
public:
    vector<pair<int, long long>> adj[50005];
    long long dist1[50005];
    long long dist2[50005];
    bool vis[50005];

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<bool> ans(m, false);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1], wt = edges[i][2];
            adj[u].push_back(make_pair(v, wt));
            adj[v].push_back(make_pair(u, wt));
        }
        long long INF = 1e18;
        for (int i = 0; i < n; i++) {
            dist1[i] = INF, dist2[i] = INF;
        }
        dist1[n - 1] = 0;
        priority_queue<pair<long long, int>> pq;
        pq.push(make_pair(0, n - 1));
        while (pq.size()) {
            int u = pq.top().second; long long wt = -pq.top().first;
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = it->first; long long d = it->second;
                if (dist1[v] > wt + d) {
                    dist1[v] = wt + d;
                    pq.push(make_pair(-dist1[v], v));
                }
            }
        }
        if (dist1[0] == INF) {
            return ans;
        }
        long long targ = dist1[0];
        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }
        dist2[0] = 0;
        set<pair<int, int>> st;
        pq.push(make_pair(0, 0));
        while (pq.size()) {
            int u = pq.top().second; long long wt = -pq.top().first;
            pq.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = it->first; long long d = it->second;
                if (dist2[v] > wt + d) {
                    dist2[v] = wt + d;
                    pq.push(make_pair(-dist2[v], v));
                }
                if (dist1[v] + wt + d == targ) {
                    st.insert(make_pair(min(u, v), max(u, v)));
                }
            }
        }
        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1];
            if (u > v) {
                swap(u, v);
            }
            if (st.find(make_pair(u, v)) != st.end()) {
                ans[i] = true;
            }
        }
        return ans;

    }
};