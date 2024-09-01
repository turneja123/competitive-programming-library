//https://atcoder.jp/contests/abc357/tasks/abc357_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

long long a[N], b[N];

long long segtree[4 * N];
long long sum[2][4 * N];
long long lazy[2][4 * N];

void compose(int parent, int child) {
    lazy[0][child] = (lazy[0][child] + lazy[0][parent]) % M;
    lazy[1][child] = (lazy[1][child] + lazy[1][parent]) % M;
}

void apply(int node, int l, int r) {
    sum[0][node] = (sum[0][node] + (r - l + 1) * lazy[0][node]) % M;
    segtree[node] = (segtree[node] + sum[1][node] * lazy[0][node]) % M;
    sum[1][node] = (sum[1][node] + (r - l + 1) * lazy[1][node]) % M;
    segtree[node] = (segtree[node] + sum[0][node] * lazy[1][node]) % M;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[0][node] = 0;
    lazy[1][node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, long long add, int i) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[i][node] = (lazy[i][node] + add) % M;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, i);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, i);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    sum[0][node] = (sum[0][node * 2 + 1] + sum[0][node * 2 + 2]) % M;
    sum[1][node] = (sum[1][node * 2 + 1] + sum[1][node * 2 + 2]) % M;
    segtree[node] = (segtree[node * 2 + 1] + segtree[node * 2 + 2]) % M;
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
        sum[0][node] = a[l] % M;
        sum[1][node] = b[l] % M;
        segtree[node] = a[l] * b[l] % M;;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    sum[0][node] = (sum[0][node * 2 + 1] + sum[0][node * 2 + 2]) % M;
    sum[1][node] = (sum[1][node * 2 + 1] + sum[1][node * 2 + 2]) % M;
    segtree[node] = (segtree[node * 2 + 1] + segtree[node * 2 + 2]) % M;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t < 3) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--, t--;
            incUpdate(0, 0, n - 1, l, r, x, t);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << getSum(0, n - 1, l, r, 0) % M << endl;
        }
    }
    return 0;
}
