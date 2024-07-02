//https://cses.fi/problemset/task/1737
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
    long long val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];
int ans;

void build(int node, int l, int r) {
    if (l == r) {
        nodes[node].val = a[l];
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        int ln = nodes[nodes[node].left].left, rn = nodes[nodes[node].left].right;
        nodes[node].left = idx;
        nodes[idx] = Node();
        nodes[nodes[node].left].left = ln, nodes[nodes[node].left].right = rn;
        idx++;
        update(nodes[node].left, l, mid, ind, val);
    } else {
        int ln = nodes[nodes[node].right].left, rn = nodes[nodes[node].right].right;
        nodes[node].right = idx;
        nodes[idx] = Node();
        nodes[nodes[node].right].left = ln, nodes[nodes[node].right].right = rn;
        idx++;
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

long long query(int node, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node].left, l, mid, lq, rq) + query(nodes[node].right, mid + 1, r, lq, rq);
}

int main() {
    IOS;
    int n, q, m = 1;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, n - 1);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, j, x;
            cin >> k >> j >> x;
            k--, j--;
            update(root[k], 0, n - 1, j, x);
        } else if (t == 2) {
            int k, l, r;
            cin >> k >> l >> r;
            k--, l--, r--;
            cout << query(root[k], 0, n - 1, l, r) << endl;
        } else {
            int k;
            cin >> k;
            k--;
            root[m] = idx;
            nodes[idx++] = Node();
            nodes[root[m]].left = nodes[root[k]].left;
            nodes[root[m]].right = nodes[root[k]].right;
            nodes[root[m]].val = nodes[root[k]].val;
            m++;
        }
    }
    return 0;
}
