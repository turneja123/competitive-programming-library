//https://codeforces.com/contest/1771/problem/F
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
int val[N];
pair<int, int> compr[N];
int ans;
long long h[N];

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

long long gen() {
    long long h = generator() + ((long long)generator() << 30);
    return h;
}

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
        nodes[node].val = nodes[node_prev].val ^ h[ind];
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
    nodes[node].val = nodes[nodes[node].left].val ^ nodes[nodes[node].right].val;
    return;
}

void query(int node_l, int node_r, int l, int r) {
    if (l == r) {
        ans = l;
        return;
    }
    int mid = (l + r) / 2;
    long long lf = nodes[nodes[node_r].left].val ^ nodes[nodes[node_l].left].val;

    if (lf > 0) {
        query(nodes[node_l].left, nodes[node_r].left, l, mid);
    } else {
        query(nodes[node_l].right, nodes[node_r].right, mid + 1, r);
    }
    return;
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
    for (int i = 0; i < m; i++) {
        h[i] = gen();
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, m - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, m - 1, a[i]);
    }
    cin >> q;
    int lastans = 0;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l ^= lastans, r ^= lastans;
        long long tot = nodes[root[l - 1]].val ^ nodes[root[r]].val;
        if (tot == 0) {
            cout << 0 << endl;
            lastans = 0;
        } else {
            query(root[l - 1], root[r], 0, m - 1);
            cout << val[ans] << endl;
            lastans = val[ans];
        }
    }
    return 0;
}
