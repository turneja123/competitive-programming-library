//https://toph.co/arena?practice=66903737a4f184cd2ac40192#!/p/65b13c62fb1dbd27709c36c4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long sum[4 * N];
long long segtree_dist[2][4 * N];
long long segtree_ct[4 * N];

int lazy[4 * N];

void compose(int parent, int child) {
    lazy[child] = lazy[parent];
}

void apply(int node, int l, int r) {
    if (lazy[node] == -1) {
        return;
    }
    if (lazy[node] == 1) {
        segtree_ct[node] = r - l + 1;
        segtree_dist[0][node] = 0;
        segtree_dist[1][node] = sum[r + 1] - sum[l];
    } else {
        segtree_ct[node] = 0;
        segtree_dist[0][node] = sum[r + 1] - sum[l];
        segtree_dist[1][node] = 0;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = -1;
}


void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree_dist[0][node] = segtree_dist[0][node * 2 + 1] + segtree_dist[0][node * 2 + 2];
    segtree_dist[1][node] = segtree_dist[1][node * 2 + 1] + segtree_dist[1][node * 2 + 2];
    segtree_ct[node] = segtree_ct[node * 2 + 1] + segtree_ct[node * 2 + 2];
}

long long getSum(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || lq > r || lq > rq) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_dist[n][node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1, n) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2, n);
}

long long getCt(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_ct[node];
    }
    int mid = (l + r) / 2;
    return getCt(l, mid, lq, rq, 2 * node + 1) +
           getCt(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    lazy[node] = -1;
    segtree_dist[0][node] = sum[r + 1] - sum[l];
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    for (int i = 1; i < 4 * N; i++) {
        sum[i] = sum[i - 1] + i;
    }
    int n, q;
    cin >> n >> q;
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            t -= 1;
            setUpdate(0, 0, n - 1, l, r, t);
        } else {
            int j = getCt(0, n - 1, 0, n - 1, 0);
            j--;
            long long ans = 2ll * (getSum(0, n - 1, j + 1, n - 1, 0, 1) - getSum(0, n - 1, 0, j, 0, 0)) + j + 1;
            cout << ans << endl;

        }
    }
    return 0;
}
