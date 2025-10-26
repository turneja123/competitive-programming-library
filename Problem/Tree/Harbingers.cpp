//https://dmoj.ca/problem/ceoi09p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

const int L = 0, R = 1e9;
const int MAX = 1100000;
const long long INF = 2e18;

struct Line {
    int k; ll b;
    long long f(int x) {
        return (ll)k * x + b;
    }
    Line(int k, ll b) : k(k), b(b) {}
}__attribute__((packed));
static_assert(sizeof(Line) == 12, "");

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, INF), left(-1), right(-1) {}
} __attribute__((packed));
static_assert(sizeof(Node) == 20, "");

vector<Node> nodes;
int idx = 0;
int root = 0;

ll ans[N];
int sz[N];
int s[N], v[N];
int head[N], to[2 * N], wt[2 * N], nxt[2 * N], e = 0;

void add_edge(int u, int v, int w) {
    nxt[e] = head[u];
    to[e] = v;
    wt[e] = w;
    head[u] = e++;
}

int add(int l, int r, int node, Line cur) {
    if (l > r) {
        return -1;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    bool lf = cur.f(l) < nodes[node].line.f(l);
    bool md = cur.f(mid) < nodes[node].line.f(mid);
    nodes[idx] = Node();
    nodes[idx].left = nodes[node].left;
    nodes[idx].right = nodes[node].right;
    nodes[idx].line = nodes[node].line;
    if (md) {
        nodes[idx].line = cur;
        cur = nodes[node].line;
    }
    node = idx++;
    if (l == r) {
        return node;
    }
    if (lf != md) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node(cur);
        } else {
            nodes[node].left = add(l, mid, nodes[node].left, cur);
        }
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node(cur);
        } else {
            nodes[node].right = add(mid + 1, r, nodes[node].right, cur);
        }
    }
    return node;
}

long long query(int l, int r, int node, long long x) {
    if (l > r) {
        return INF;
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
        ans = min(ans, query(l, mid, nodes[node].left, x));
    }
    if (x > mid && nodes[node].right != -1) {
        ans = min(ans, query(mid + 1, r, nodes[node].right, x));
    }
    return ans;
}

pair<int, int> restore[N];
int m = 0;

int par_[N], it_[N], st_[N];
int eu_node[2 * N];
int eu_enter[2 * N];
int tim = 0;

void dfs() {
    int top = 0;
    st_[top] = 0; par_[0] = -1; it_[0] = head[0]; sz[0] = 0;

    eu_node[tim] = 0; eu_enter[tim++] = 1;

    while (top >= 0) {
        int u = st_[top];
        int &e = it_[u];
        while (e != -1 && to[e] == par_[u]) {
            e = nxt[e];
        }
        if (e == -1) {
            eu_node[tim] = u; eu_enter[tim++] = 0;
            top--;
            continue;
        }
        int w = to[e], wwt = wt[e];
        e = nxt[e];
        par_[w] = u;
        sz[w] = sz[u] + wwt;
        st_[++top] = w;
        it_[w] = head[w];

        eu_node[tim] = w; eu_enter[tim++] = 1;
    }
}

int main() {
    IOS;

    for (int i = 0; i < N; i++) {
        head[i] = -1;
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    for (int i = 1; i < n; i++) {
        cin >> s[i] >> v[i];
    }
    dfs();

    nodes.resize(MAX);
    nodes[idx] = Node();
    restore[m++] = {idx++, idx};
    for (int i = 0; i < tim; i++) {
        int u = eu_node[i];
        if (eu_enter[i]) {
            restore[m++] = {root, idx};
            if (u == 0) {
                Line line = Line(0, 0);
                root = add(L, R, root, line);
            } else {
                ans[u] = (ll)sz[u] * v[u] + s[u] + query(L, R, root, v[u]);
                Line line = Line(-sz[u], ans[u]);
                root = add(L, R, root, line);
            }
        } else {
            auto [x, y] = restore[m - 1];
            m--;
            root = x; idx = y;
        }
    }


    for (int i = 1; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
