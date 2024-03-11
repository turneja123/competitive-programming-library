//https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(k + 1, INF));
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < flights.size(); i++) {
            adj[flights[i][0]].push_back(make_pair(flights[i][1], flights[i][2]));
        }
        dist[src][0] = 0; 
        priority_queue<pair<int, pair<int, int>>> pq;
        pq.push(make_pair(0, make_pair(src, 0)));
        while (pq.size()) {
            int d = -pq.top().first;
            int u = pq.top().second.first;
            int m = pq.top().second.second;
            pq.pop();
            if (vis[u][m] || u == dst) {
                continue;
            }
            vis[u][m] = true;
            for (int i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first, wt = adj[u][i].second, s = m + 1;
                if (v == dst) {
                    s--;
                }
                if (s <= k && !vis[v][s] && d + wt < dist[v][s]) {
                    dist[v][s] = d + wt;
                    pq.push(make_pair(-dist[v][s], make_pair(v, s)));
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= k; i++) {
            ans = min(ans, dist[dst][i]);
        }
        if (ans == INF) {
            return -1;
        }
        return ans;

    }
};