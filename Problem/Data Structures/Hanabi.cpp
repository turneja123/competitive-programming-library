//https://codeforces.com/contest/2207/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int forced[N];
int skip[N];
int mx[N];

vector<int> v[N];
vector<int> add[N];

struct Node {
    int lazy;
    int mx;
    Node() {
        lazy = 0; mx = -INF;
    }
    Node(int x) {
        lazy = 0;
        mx = x;

    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mx = max(left.mx, right.mx);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].mx += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void upd(int node, int l, int r, int ind, int val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(2 * node + 1, l, mid, ind, val);
    } else {
        upd(2 * node + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return -INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].mx;
    }
    int mid = (l + r) / 2;
    return max(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node();
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> a(n * m);

        for (int i = 0; i < n * m; i++) {
            cin >> a[i].first;
        }
        for (int i = 0; i < n * m; i++) {
            cin >> a[i].second;
        }

        for (int i = 0; i < n * m; i++) {
            auto [r, c] = a[i];
            if (mx[c] > r) {
                forced[r] = 1;
                skip[i] = 1;
            }
            mx[c] = max(mx[c], r);
        }

        vector<pair<int, int>> ivals;
        int cost = 0;
        for (int i = 1; i <= n; i++) {
            if (forced[i]) {
                cost++;
                ivals.push_back({i, i});
            }
        }
        for (int i = 0; i < n * m; i++) {
            auto [r, c] = a[i];
            if (!skip[i]) {
                v[c].push_back(r);
            }
        }

        for (int i = 1; i <= m; i++) {
            if (v[i].empty()) {
                continue;
            }
            cost++;
            int l = v[i][0], r = v[i][0];
            for (int j = 1; j < v[i].size(); j++) {
                if (v[i][j] - r > 1) {
                    cost++;
                    ivals.push_back({l, r});
                    l = v[i][j], r = v[i][j];
                } else {
                    r = v[i][j];
                }
            }
            ivals.push_back({l, r});
        }

        for (auto [l, r] : ivals) {
            add[r].push_back(l);
        }
        build(0, n, 0);
        int best = 0;
        upd(0, 0, n, 0, 0);

        for (int i = 1; i <= n; i++) {
            for (int l : add[i]) {
                incUpdate(0, 0, n, 0, l - 1, 1);
            }
            int dp = max(best, query(0, n, 0, i - 1, 0) - i);
            best = max(best, dp);
            upd(0, 0, n, i, dp + i);
        }

        cout << cost - best - 1 << endl;
        for (int i = 0; i <= n * m; i++) {
            forced[i] = 0;
            mx[i] = 0;
            skip[i] = 0;
            add[i].clear();
            v[i].clear();
        }

    }

    return 0;
}
