//https://leetcode.com/contest/weekly-contest-346/problems/modify-graph-edge-weights/
const int N = 105;
const int INF = 2e9;
class Solution {
public:
    vector<tuple<int, int, int>> adj[N];
    int dist[N][N];
    pair<int, int> parent[N][N];

    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        int m = edges.size();
        for (int i = 0; i < m; i++) {
            adj[edges[i][0]].push_back(make_tuple(edges[i][1], edges[i][2], i));
            adj[edges[i][1]].push_back(make_tuple(edges[i][0], edges[i][2], i));
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = INF;
            }
        }
        dist[source][0] = 0;
        priority_queue<tuple<int, int, int>> pq;
        pq.push(make_tuple(0, source, 0));
        while (pq.size()) {
            auto [d, u, j] = pq.top();
            d = -d;
            pq.pop();
            if (dist[u][j] != d) {
                continue;
            }
            for (auto [v, wt, e] : adj[u]) {
                if (wt == -1) {
                    if (j < n && dist[v][j + 1] > dist[u][j]) {
                        dist[v][j + 1] = dist[u][j];
                        parent[v][j + 1] = make_pair(u, e);
                        pq.push(make_tuple(-dist[v][j + 1], v, j + 1));
                    }
                } else {
                    if (j < n && dist[v][j] > dist[u][j] + wt) {
                        dist[v][j] = dist[u][j] + wt;
                        parent[v][j] = make_pair(u, e);
                        pq.push(make_tuple(-dist[v][j], v, j));
                    }
                }
            }
        }
        vector<vector<int>> ans;
        if (dist[destination][0] < target) {
            return ans;
        }
        if (dist[destination][0] == target) {
            for (int i = 0; i < m; i++) {
                if (edges[i][2] == -1) {
                    edges[i][2] = INF;
                }
            }
            return edges;
        }
        for (int j = 1; j < n; j++) {
            if (dist[destination][j] + j <= target) {
                int u = destination;
                vector<int> ve;
                int jj = j;
                while (u != source) {
                    auto [v, e] = parent[u][jj];
                    if (edges[e][2] == -1) {
                        ve.push_back(e);
                        jj--;
                    }
                    u = v;
                }
                for (int e : ve) {
                    edges[e][2] = 1;
                }
                edges[ve[0]][2] += target - (dist[destination][j] + j);
                for (int i = 0; i < m; i++) {
                    if (edges[i][2] == -1) {
                        edges[i][2] = INF;
                    }
                }
                return edges;
            }
        }
        return ans;


    }
};
