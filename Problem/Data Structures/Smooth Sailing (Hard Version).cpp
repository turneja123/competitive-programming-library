//https://codeforces.com/contest/1920/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int K = 21;

string s[N];
vector<pair<int, int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<pair<int, int>> moves{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int parent[N];
int tin[N];
int tout[N];
int up[K][N];
int val[N];
int timer = 0;

vector<int> adj[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void add_edge(int u, int v, int e) {
    u = dsu_find(u), v = dsu_find(v);
    if (u == v) {
        parent[e] = -1;
        return;
    }
    parent[u] = e;
    parent[v] = e;
    parent[e] = e;
    adj[e].push_back(v);
    adj[e].push_back(u);
    adj[u].push_back(e);
    adj[v].push_back(e);
    return;
}

void dfs(int u, int p) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    int R, C, Q;
    cin >> R >> C >> Q;
    vector<pair<int, int>> a;
    vector<tuple<int, int, int, int, int, int>> queries;
    vector<int> inds;
    int mnx, mny;
    for (int i = 0; i < R; i++) {
        cin >> s[i];
        for (int j = 0; j < C; j++) {
            if (s[i][j] == '#') {
                mnx = i;
                mny = j;
            }
            int x = i + 1, y = j + 1;
            if (s[i][j] == 'v') {
                a.push_back(make_pair(x - y, x + y));
            }
            queries.push_back(make_tuple(x - y, x + y, 0, N - 1, queries.size(), 1));
            inds.push_back(inds.size());
        }
    }
    sort(a.begin(), a.end());
    int m = queries.size(), n = a.size();
    vector<int> ans(m);
    while (true) {
        if (inds.empty()) {
            break;
        }

        vector<int> ct(m, 0);
        vector<tuple<int, int, int, int>> events;
        for (int j : inds) {
            auto [x, y, l, r, i, k] = queries[j];
            int mid = (l + r) / 2;
            events.push_back(make_tuple(x - mid - 1, max(1, y - mid), min(N - 1, y + mid), ~i));
            events.push_back(make_tuple(x + mid, max(1, y - mid), min(N - 1, y + mid), i));
        }
        sort(events.begin(), events.end());
        int ptr = 0;
        BIT bit(N);
        for (auto [x, yl, yr, i] : events) {
            while (ptr < n && a[ptr].first <= x) {
                bit.upd(a[ptr].second, 1);
                ptr++;
            }
            if (i < 0) {
                i = ~i;
                ct[i] -= bit.query(yl, yr);
            } else {
                ct[i] += bit.query(yl, yr);
            }
        }

        vector<int> nx;
        for (int j : inds) {
            auto [x, y, l, r, i, k] = queries[j];
            int mid = (l + r) / 2;
            if (ct[i] >= k) {
                ans[i] = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
            queries[j] = make_tuple(x, y, l, r, i, k);
            if (l <= r) {
                nx.push_back(i);
            }
        }
        inds = nx;
    }
    vector<vector<int>> dist(R, vector<int>(C, 0));
    for (int i = 0; i < R * C; i++) {
        int x = i / C, y = i % C;
        dist[x][y] = ans[i];
    }
    int e = 2 * R * C;
    for (int i = 0; i < e; i++) {
        parent[i] = i;
    }
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (s[i][j] == '#') {
                continue;
            }
            if (i != R - 1 && s[i + 1][j] != '#') {
                int wt = min(dist[i][j], dist[i + 1][j]);

                if (i == mnx - 1 && j > mny) {
                    edges.push_back({wt, i * C + j, R * C + (i + 1) * C + j});
                    edges.push_back({wt, i * C + j + R * C, (i + 1) * C + j});
                } else {
                    edges.push_back({wt, i * C + j, (i + 1) * C + j});
                    edges.push_back({wt, i * C + j + R * C, (i + 1) * C + j + R * C});
                }
            }
            if (j != C - 1 && s[i][j + 1] != '#') {
                int wt = min(dist[i][j], dist[i][j + 1]);
                edges.push_back({wt, i * C + j, i * C + j + 1});
                edges.push_back({wt, i * C + j + R * C, i * C + j + 1 + R * C});
            }
        }
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    for (auto [wt, u, v] : edges) {
        add_edge(u, v, e);
        val[e] = wt;
        e++;
    }
    int root = dsu_find(0);
    dfs(root, root);
    for (int i = 0; i < Q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << val[lca(x * C + y, x * C + y + R * C)] << endl;
    }

    return 0;
}
