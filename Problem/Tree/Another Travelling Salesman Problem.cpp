//https://www.spoj.com/problems/YOSALES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int L = 0, R = 1e9;
const int MAX = 1e6;
const long long INF = 2e18;

long long a[N];
long long b[N];

int sz[N];
bool seen_c[N];
int parent_c[N];
long long depth[N];
vector<pair<int, int>> adj[N];

long long ans = 0;

struct Line {
    long long k, b;
    long long f(long long x) {
        return k * x + b;
    }
    Line(long long k, long long b) : k(k), b(b) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, -INF), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

void add(int l, int r, int node, Line cur) {
    if (l > r) {
        return;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    bool lf = cur.f(l) > nodes[node].line.f(l);
    bool md = cur.f(mid) > nodes[node].line.f(mid);
    if (md) {
        swap(nodes[node].line, cur);
    }
    if (l == r) {
        return;
    }
    if (lf != md) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(cur);
        } else {
            add(l, mid, nodes[node].left, cur);
        }
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(cur);
        } else {
            add(mid + 1, r, nodes[node].right, cur);
        }
    }
    return;
}

long long query(int l, int r, int node, long long x) {
    if (l > r) {
        return -INF;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    long long ans = nodes[node].line.f(x);
    if (l == r) {
        return ans;
    }
    if (x <= mid && nodes[node].left != -1) {
        ans = max(ans, query(l, mid, nodes[node].left, x));
    }
    if (x > mid && nodes[node].right != -1) {
        ans = max(ans, query(mid + 1, r, nodes[node].right, x));
    }
    return ans;
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

void dfs_depth1(int u, int p) {
    Line cur(a[u], -a[u] * b[u] - depth[u]);
    add(0, R - 1, 0, cur);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + wt;
            dfs_depth1(v, u);
        }
    }
    return;
}

void dfs_depth2(int u, int p) {
    ans = max(ans, query(0, R - 1, 0, b[u]) - depth[u]);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth2(v, u);
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

    idx = 0;
    nodes[idx++] = Node();
    Line cur(a[c], -a[c] * b[c]);
    add(0, R - 1, 0, cur);

    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = wt;
            dfs_depth1(v, c);
        }
    }

    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = wt;
            dfs_depth2(v, c);
        }
    }
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    build(0, -1);
    cout << ans;


    return 0;
}
