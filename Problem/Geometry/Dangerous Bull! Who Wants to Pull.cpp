//https://lightoj.com/problem/dangerous-bull-who-wants-to-p
#include <bits/stdc++.h>

using namespace std;

const double INF = 1e18;
const double EPS = 1e-9;

struct Point {
    double x, y;
};

struct Edge {
    int u, v;
    double w;
    int id;
};

double dist(Point p1, Point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

double cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int n;
Point bull;
vector<Point> pts;
vector<pair<int, int>> raw_edges;

void solve(int t) {
    pts.clear();
    raw_edges.clear();

    cin >> n >> bull.x >> bull.y;

    map<pair<int, int>, int> pt_map;
    int pt_cnt = 0;

    auto get_pt_id = [&](int x, int y) {
        if (pt_map.find({x, y}) == pt_map.end()) {
            pt_map[{x, y}] = pt_cnt++;
            pts.push_back({(double)x, (double)y});
        }
        return pt_map[{x, y}];
    };

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int u = get_pt_id(x1, y1);
        int v = get_pt_id(x2, y2);
        raw_edges.push_back({u, v});
    }

    vector<Edge> edges;
    for (auto& p : raw_edges) {
        int u = p.first;
        int v = p.second;

        if (cross_product(pts[u], pts[v], bull) > EPS) {
            edges.push_back({u, v, dist(pts[u], pts[v]), (int)edges.size()});
        }
        if (cross_product(pts[v], pts[u], bull) > EPS) {
            edges.push_back({v, u, dist(pts[v], pts[u]), (int)edges.size()});
        }
    }

    int m = edges.size();
    vector<vector<int>> adj(m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (edges[i].v == edges[j].u) {
                if (cross_product(pts[edges[i].u], pts[edges[i].v], pts[edges[j].v]) > -EPS) {
                    adj[i].push_back(j);
                }
            }
        }
    }

    double min_len = INF;

    for (int start_node = 0; start_node < m; ++start_node) {
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        vector<double> d(m, INF);

        d[start_node] = edges[start_node].w;
        pq.push({d[start_node], start_node});

        while (!pq.empty()) {
            double cd = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (cd > d[u]) continue;
            if (cd > min_len) break;

            for (int v : adj[u]) {
                if (v == start_node) {
                    min_len = min(min_len, cd);
                } else {
                    if (d[u] + edges[v].w < d[v]) {
                        d[v] = d[u] + edges[v].w;
                        pq.push({d[v], v});
                    }
                }
            }
        }
    }

    if (min_len >= INF) {
        printf("Case %d: -1.000\n", t);
    } else {
        printf("Case %d: %.10f\n", t, 2.0 * min_len);
    }
}

int main() {
    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; ++i) {
            solve(i);
        }
    }
    return 0;
}
