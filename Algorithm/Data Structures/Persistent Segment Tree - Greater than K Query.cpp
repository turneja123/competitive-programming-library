//https://www.spoj.com/problems/KQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];
int val[N];
pair<int, int> compr[N];
int ans;

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + 1;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val - nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        val[m] = a[compr[i].second];
        a[compr[i].second] = m;
    }
    m++;
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, m - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, m - 1, a[i]);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int ind = upper_bound(val, val + m, k) - val;
        if (ind == m) {
            cout << 0 << endl;
        } else {
            cout << query(root[l - 1], root[r], 0, m - 1, ind, m - 1) << endl;
        }
    }
    return 0;
}
