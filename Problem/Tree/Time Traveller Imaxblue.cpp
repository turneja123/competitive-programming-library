//https://dmoj.ca/problem/tc19summerh
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 3e7;
const long long INF = 2e18;


mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, long long, custom_hash> dist[N];
int sz[N];
bool seen_c[N];
int parent_c[N];
long long depth[N];
vector<pair<int, int>> adj[N];

struct Node {
    long long val;
    int left;
    int right;
    Node() : val(INF), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

long long query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return INF;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2;
    long long ans = INF;
    if (nodes[node].left != -1) {
        ans = min(ans, query(nodes[node].left, l, mid, lq, rq));
    }
    if (nodes[node].right != -1) {
        ans = min(ans, query(nodes[node].right, mid + 1, r, lq, rq));
    }
    return ans;

}

void update(int node, int l, int r, int ind, long long val) {
    if (l == r) {
        nodes[node].val = min(nodes[node].val, val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = INF;
    if (nodes[node].left != -1) {
        nodes[node].val = min(nodes[node].val, nodes[nodes[node].left].val);
    }
    if (nodes[node].right != -1) {
        nodes[node].val = min(nodes[node].val, nodes[nodes[node].right].val);
    }
}

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth(int u, int p, int c) {
    dist[c][u] = depth[u];
    for (auto [v, wt]: adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + wt;
            dfs_depth(v, u, c);
        }
    }
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;
    dist[c][c] = 0;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = wt;
            dfs_depth(v, v, c);
        }
    }
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

void upd_cent(int u, int t, long long wt) {
    int c = u;
    while (1) {
        long long s = wt + dist[c][u];
        update(c, 0, N - 1, t, s);
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
    }
    return;
}

long long query_cent(int u, int t) {
    long long best = INF;
    int c = u;
    while (1) {
        best = min(best, dist[c][u] + query(c, 0, N - 1, 0, t));
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
    }
    return best;
}

int main() {
    IOS;
    int n, m, q, t;
    cin >> n >> m >> q >> t;
    for (int i = 0; i < n; i++) {
        nodes[idx++] = Node();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    vector<tuple<int, int, int, int>> portals;

    for (int i = 0; i < m; i++) {
        int u, s, e, w;
        cin >> u >> s >> e >> w;
        portals.push_back(make_tuple(s, e, w, u));
    }
    build(0, -1);
    sort(portals.begin(), portals.end());
    reverse(portals.begin(), portals.end());
    upd_cent(0, t, 0);
    for (auto [s, e, w, u] : portals) {
        long long tim = query_cent(u, s);
        if (tim != INF) {
            upd_cent(u, e, tim + w);
        }
    }
    for (int i = 0; i < q; i++) {
        int s, u;
        cin >> s >> u;
        long long ans = query_cent(u, s);
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << endl;
    }



    return 0;
}
