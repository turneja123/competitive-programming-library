//https://leetcode.com/problems/minimum-total-distance-traveled/description/
class Solution {
public:
    const long long INF = 1e18;

    struct Edge {
        int u, v;
        long long cap, cost;
        Edge(int u, int v, long long cap, long long cost) : u(u), v(v), cap(cap), cost(cost) {}
    };

    vector<int> adj[1005];
    vector<Edge> edges;

    void add_edge(int u, int v, int cap, int cost) {
        adj[u].push_back(edges.size());
        edges.emplace_back(u, v, cap, cost);
        adj[v].push_back(edges.size());
        edges.emplace_back(v, u, 0, -cost);
    }

    void shortest_paths(int n, int v0, vector<long long>& d, vector<long long>& p) {
        d.assign(n, INF);
        d[v0] = 0;
        priority_queue<pair<long long, int>> q;
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

    long long min_cost_flow(int N, int K, int s, int t) {
        long long flow = 0;
        long long ans = 0;
        vector<long long> d, p;
        while (flow < K) {
            shortest_paths(N, s, d, p);
            if (d[t] == INF) {
                break;
            }

            long long f = K - flow;
            long long cur = t;
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


    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int n = robot.size(), m = factory.size();
        int s = 0, t = 1 + n + m;
        for (int i = 0; i < n; i++) {
            add_edge(s, i + 1, 1, 0);
        }
        for (int i = 0; i < m; i++) {
            add_edge(i + n + 1, t, factory[i][1], 0);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int d = abs(robot[i] - factory[j][0]);
                add_edge(i + 1, j + n + 1, 1, d);
            }
        }

        return min_cost_flow(t + 1, n, s, t);
    }
};
