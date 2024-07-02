//https://judge.yosupo.jp/problem/range_kth_smallest
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

void query(int node_l, int node_r, int l, int r, int k) {
    if (l == r) {
        ans = l;
        return;
    }
    int mid = (l + r) / 2;
    int ct = nodes[nodes[node_r].left].val - nodes[nodes[node_l].left].val;
    if (ct > k) {
        query(nodes[node_l].left, nodes[node_r].left, l, mid, k);
    } else {
        query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, k - ct);
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
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
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        query(root[l], root[r], 0, m - 1, k);
        cout << val[ans] << endl;
    }
    return 0;
}
