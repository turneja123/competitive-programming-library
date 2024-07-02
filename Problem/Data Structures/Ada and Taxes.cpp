//https://www.spoj.com/problems/ADATAXES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 1e7 + 5;
const int M = 1e9 + 7;

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
int pos[N];
pair<int, int> compr[N];
int ans;

int modInverse(int a) {
    int res = 1;
    int y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (long long)res * a % M;
        }
        y /= 2;
        a = (long long)a * a % M;
    }
    return res;
}

void build(int node, int l, int r) {
    if (l == r) {
        nodes[node].val = 1;
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    nodes[node].val = 1;
    return;
}

void update(int node_prev, int node, int l, int r, int ind) {
    if (l == r) {
        nodes[node].val = (long long)nodes[node_prev].val * val[l] % M;
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
    nodes[node].val = (long long)nodes[nodes[node].left].val * nodes[nodes[node].right].val % M;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 1;
    }
    if (lq <= l && rq >= r) {
        return (long long)nodes[node_r].val * modInverse(nodes[node_l].val) % M;
    }
    int mid = (l + r) / 2;
    return (long long)query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) * query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq) % M;
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
        pos[compr[i].second] = m;
    }
    m++;
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, m - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, m - 1, pos[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        if (k < val[0]) {
            cout << 1 << endl;
            continue;
        }
        l++, r++;
        int ind = upper_bound(val, val + m, k) - val;
        cout << query(root[l - 1], root[r], 0, m - 1, 0, ind - 1) << endl;
    }
    return 0;
}
