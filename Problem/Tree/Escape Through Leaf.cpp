//https://codeforces.com/contest/932/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int L = -1e5 + 5, R = 1e5 + 5;

const int N = 1e5 + 5;
const int MAX = 5e6;
const long long INF = 2e18;

long long a[N];
long long b[N];
long long dp[N];

int parent[N];
vector<int> adj[N];

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
    Node() : line(0, INF), left(-1), right(-1) {}
};

vector<Line> st[N];
Node nodes[MAX];
int idx = 0;

void add(int l, int r, int lq, int rq, int node, Line cur) {
    if (l > r || l > rq || r < lq) {
        return;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    if (l >= lq && r <= rq) {
        bool lf = cur.f(l) < nodes[node].line.f(l);
        bool md = cur.f(mid) < nodes[node].line.f(mid);
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
                add(l, mid, lq, rq, nodes[node].left, cur);
            }
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node(cur);
            } else {
                add(mid + 1, r, lq, rq, nodes[node].right, cur);
            }
        }
        return;
    }
    if (l == r) {
        return;
    }
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(l, mid, lq, rq, nodes[node].left, cur);
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(mid + 1, r, lq, rq, nodes[node].right, cur);
    }

    return;
}

long long query(int l, int r, int lq, int rq, int node, long long x) {
    if (l > r || l > rq || r < lq) {
        return INF;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    if (l >= lq && r <= rq) {
        long long ans = nodes[node].line.f(x);
        if (l == r) {
            return ans;
        }
        if (x <= mid && nodes[node].left != -1) {
            ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
        }
        if (x > mid && nodes[node].right != -1) {
            ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
        }
        return ans;
    }
    long long ans = INF;
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
    }
    return ans;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (int i = 0; i < st[a].size(); i++) {
        add(L, R, L, R, b, st[a][i]);
        st[b].push_back(st[a][i]);
    }

    return;
}


void dfs(int u, int p) {
    int deg = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            deg++;
        }
    }
    if (deg == 0) {
        dp[u] = 0;
        Line line(b[u], 0);
        add(L, R, L, R, u, line);
        st[u].push_back(line);
        return;
    }
    dp[u] = INF;
    for (int v : adj[u]) {
        if (v != p) {
            int x = dsu_find(u), y = dsu_find(v);
            dp[u] = min(dp[u], query(L, R, L, R, y, a[u]));
            dsu_merge(x, y);
        }
    }
    int x = dsu_find(u);
    Line line(b[u], dp[u]);
    add(L, R, L, R, x, line);
    st[x].push_back(line);
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
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        nodes[idx++] = Node();
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
    }

    return 0;
}
