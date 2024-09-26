//https://www.spoj.com/problems/QUERYIT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

int a[N];
int segtree[2][4 * N];
int ct[2][4 * N];
int lazy[4 * N];
string s;

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    if (lazy[node] % 2 == 1) {
        swap(segtree[0][node], segtree[1][node]);
        swap(ct[0][node], ct[1][node]);
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += 1;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    ct[0][node] = ct[0][node * 2 + 1] + ct[0][node * 2 + 2];
    ct[1][node] = ct[1][node * 2 + 1] + ct[1][node * 2 + 2];
    segtree[0][node] = max({ct[0][node], segtree[0][2 * node + 1] + ct[0][2 * node + 2], ct[1][2 * node + 1] + segtree[0][2 * node + 2]});
    segtree[1][node] = max({ct[1][node], segtree[1][2 * node + 1] + ct[1][2 * node + 2], ct[0][2 * node + 1] + segtree[1][2 * node + 2]});
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        ct[a[l]][node] = 1;
        segtree[0][node] = 1;
        segtree[1][node] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    ct[0][node] = ct[0][node * 2 + 1] + ct[0][node * 2 + 2];
    ct[1][node] = ct[1][node * 2 + 1] + ct[1][node * 2 + 2];
    segtree[0][node] = max({ct[0][node], segtree[0][2 * node + 1] + ct[0][2 * node + 2], ct[1][2 * node + 1] + segtree[0][2 * node + 2]});
    segtree[1][node] = max({ct[1][node], segtree[1][2 * node + 1] + ct[1][2 * node + 2], ct[0][2 * node + 1] + segtree[1][2 * node + 2]});
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            incUpdate(0, 0, n - 1, l, r);
        } else {
            apply(0, 0, n - 1);
            cout << segtree[1][0] << endl;
        }
    }
    return 0;
}
