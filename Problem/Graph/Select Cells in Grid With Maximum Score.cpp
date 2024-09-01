//https://leetcode.com/contest/weekly-contest-413/problems/select-cells-in-grid-with-maximum-score/
class Solution {
public:
    const int INF = 1e9;


    struct Edge {
        int u, v;
        int cap, cost;
        Edge(int u, int v, int cap, int cost) : u(u), v(v), cap(cap), cost(cost) {}
    };

    vector<int> adj[1005];
    vector<Edge> edges;

    bool b[105];

    void add_edge(int u, int v, int cap, int cost) {
        adj[u].push_back(edges.size());
        edges.emplace_back(u, v, cap, cost);
        adj[v].push_back(edges.size());
        edges.emplace_back(v, u, 0, -cost);
    }

    void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
        d.assign(n, INF);
        d[v0] = 0;
        priority_queue<pair<int, int>> q;
        q.push(make_pair(0, v0));
        p.assign(n, -1);
        while (!q.empty()) {
            int u = q.top().second, nw = -q.top().first;
            q.pop();
            if (nw != d[u]) {
                continue;
            }
            for (int e : adj[u]) {
                int v = edges[e].v;
                if (edges[e].cap > 0 && d[v] > d[u] + edges[e].cost) {
                    d[v] = d[u] + edges[e].cost;
                    p[v] = e;
                    q.push(make_pair(-d[v], v));

                }
            }
        }
    }

    int min_cost_flow(int N, int K, int s, int t) {
        int flow = 0;
        int ans = 0;
        vector<int> d, p;
        while (flow < K) {
            shortest_paths(N, s, d, p);
            if (d[t] == INF) {
                break;
            }

            int f = K - flow;
            int cur = t;
            while (cur != s) {
                f = min(f, edges[p[cur]].cap);
                cur = edges[p[cur]].u;
            }
            flow += f;
            ans += f * d[t];
            cur = t;
            while (cur != s) {
                edges[p[cur]].cap -= f;
                edges[p[cur] ^ 1].cap += f;
                cur = edges[p[cur]].u;
            }
        }

        return ans;
    }

    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int s = 0, t = 1 + 100 + n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                b[grid[i][j]] = true;
                add_edge(grid[i][j], 1 + 100 + i, 1, -grid[i][j]);
            }
            add_edge(1 + 100 + i, t, 1, 0);
        }
        for (int i = 1; i <= 100; i++) {
            if (b[i]) {
                add_edge(s, i, 1, 0);
            }
        }
        return -min_cost_flow(2 + 100 + n, n, s, t);

    }
};
