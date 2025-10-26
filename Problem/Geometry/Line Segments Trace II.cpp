//https://cses.fi/problemset/task/3428/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1e5 + 5;

const int L = 0, R = 1e5 + 5;
const int MAX = 2e6;
const long long INF = 2e18;

struct Line {
    ld k, b;
    ld f(long long x) {
        return k * x + b;
    }
    Line(ld k, ld b) : k(k), b(b) {}
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
int root = 0;

vector<pair<int, int>> restore;
vector<Line> segtree[4 * N];
long long ans[N];

int add(int l, int r, int node, Line cur) {
    if (l > r) {
        return -1;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    bool lf = cur.f(l) > nodes[node].line.f(l);
    bool md = cur.f(mid) > nodes[node].line.f(mid);
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

ld query(int l, int r, int node, long long x) {
    if (l > r) {
        return -INF;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    ld ans = nodes[node].line.f(x);
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

void upd(int l, int r, int lq, int rq, Line edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node) {
    int ct = 0;
    for (Line line : segtree[node]) {
        ct++;
        restore.push_back({root, idx});
        root = add(L, R, root, line);
    }
    if (l == r) {
        ans[l] = floor(query(L, R, root, l));
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [x, y] = restore.back();
        restore.pop_back();
        root = x; idx = y;
    }
    return;
}

int main() {
    IOS;
    nodes[idx] = Node();
    restore.push_back({idx++, idx});
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        ld k = (x1 == x2 ? 0.0 : (ld)(y2 - y1) / (ld)(x2 - x1));
        ld b = (ld)y1 - k * (ld)x1;
        Line cur(k, b);
        upd(0, m, x1, x2, cur, 0);
    }

    dfs(0, m, 0);
    for (int i = 0; i <= m; i++) {
        if (ans[i] < 0) {
            ans[i] = -1;
        }
        cout << ans[i] << " ";
    }
    return 0;
}
