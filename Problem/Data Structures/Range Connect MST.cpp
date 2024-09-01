//https://atcoder.jp/contests/abc364/tasks/abc364_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e7;

tuple<int, int, int> edge[MAX];
pair<int, int> lr[N];
tuple<int, int, int> queries[N];

long long segtree[4 * N];
long long setVal[4 * N];
bool setValid[4 * N];

int parent[2 * N];
int sz[2 * N];

int dsu_find(int a) {
    while (parent[a] != a) {
        a = parent[a];
    }
    return a;
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node];
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

long long getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

int main() {
    IOS;
    int n, q, m = 0;
    cin >> n >> q;
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        queries[i] = make_tuple(x, l, r);
    }
    sort(queries, queries + q);
    for (int i = 0; i < q; i++) {
        int l = get<1>(queries[i]), r = get<2>(queries[i]), x = get<0>(queries[i]);
        l--, r--;
        int b = getSum(0, n - 1, r, r, 0);
        if (b != -1) {
            r = lr[b].second;
        }
        int a = getSum(0, n - 1, l, l, 0);
        if (a != -1) {
            l = lr[a].first;
        }
        lr[i] = make_pair(l, r);
        int j = l;
        while (j <= r) {
            edge[m++] = make_tuple(x, n + i, j);
            int pos = getSum(0, n - 1, j, j, 0);
            if (pos == -1) {
                j++;
            } else {
                j = lr[pos].second + 1;
            }
        }
        setUpdate(0, 0, n - 1, l, r, i);
    }
    if (lr[q - 1].first != 0 || lr[q - 1].second != n - 1) {
        cout << -1;
        return 0;
    }
    sort(edge, edge + m);
    for (int i = 0; i < n + q; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    long long len = 0;
    for (int i = 0; i < m; i++) {
        long long wt = get<0>(edge[i]);
        int a = get<1>(edge[i]);
        int b = get<2>(edge[i]);
        int p1 = dsu_find(a);
        int p2 = dsu_find(b);
        if (p1 != p2) {
            dsu_unite(p1, p2);
            len += wt;
        }
    }
    cout << len;
    return 0;
}
