//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 6e6 + 5;
const ll INF = 1e18;
const int R = 1e6 + 5;

struct Line {
    ll k, b;
    ll f(ll x) {
        return k * x + b;
    }
};


struct Node {
    int l;
    int r;
    Line line;
    Node() {
        l = -1;
        r = -1;
        line = {0, -INF};
    }
    Node(Line _line) {
        l = -1;
        r = -1;
        line = _line;
    }
};


Node nodes[MAX];
int idx = 0;

void add(int l, int r, int node, Line line) {
    int mid = (l + r) / 2;
    if (r - l == 1) {
        mid = l;
    }
    bool lf = line.f(l) > nodes[node].line.f(l);
    bool md = line.f(mid) > nodes[node].line.f(mid);
    if (md) {
        swap(line, nodes[node].line);
    }
    if (l == r) {
        return;
    }
    if (lf != md) {
        if (nodes[node].l == -1) {
            nodes[node].l = idx;
            nodes[idx++] = Node(line);
            return;
        }
        add(l, mid, nodes[node].l, line);
    } else {
        if (nodes[node].r == -1) {
            nodes[node].r = idx;
            nodes[idx++] = Node(line);
            return;
        }
        add(mid + 1, r, nodes[node].r, line);
    }
}

ll query(int l, int r, int node, int x) {

    ll ans = nodes[node].line.f(x);
    if (l == r) {
        return ans;
    }
    int mid = (l + r) / 2;
    if (r - l == 1) {
        mid = l;
    }

    if (x <= mid && nodes[node].l != -1) {
        ans = max(ans, query(l, mid, nodes[node].l, x));
    }
    if (x > mid && nodes[node].r != -1) {
        ans = max(ans, query(mid + 1, r, nodes[node].r, x));
    }
    return ans;
}

int segtree[4 * N];

ll getMax(int l, int r, int node, int lq, int rq, int x) {
    if (l > rq || r < lq) {
        return -INF;
    }
    if (l >= lq && r <= rq) {
        return query(-R, R, segtree[node], x);
    }
    int mid = (l + r) / 2;
    return max(getMax(l, mid, 2 * node + 1, lq, rq, x), getMax(mid + 1, r, 2 * node + 2, lq, rq, x));
}

void update(int l, int r, int node, int ind, Line line) {
    add(-R, R, segtree[node], line);
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, ind, line);
    } else {
        update(mid + 1, r, 2 * node + 2, ind, line);
    }
}

void build(int l, int r, int node) {
    segtree[node] = idx;
    nodes[idx++] = Node();
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < k; i++) {
        int h, s, e, v;
        cin >> h >> s >> e >> v;
        queries.push_back({e, s, v});

    }
    build(0, N, 0);
    sort(queries.begin(), queries.end());
    ll ans = -INF;
    update(0, N, 0, 0, {0, 0});
    for (auto [e, s, v] : queries) {
        ll dp = getMax(0, N, 0, s - 1, e - 1, v) + (ll)e * v;
        if (e == m) {
            ans = max(ans, dp);
        }
        update(0, N, 0, e, {-e, dp});
    }
    cout << ans;
    return 0;
}
