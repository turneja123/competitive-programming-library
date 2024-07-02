//https://www.spoj.com/problems/LGLOVE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

int a[N];
int segtree_min[4 * N];
int segtree_max[4 * N];
int lazy[4 * N];
long long ans[3 * N];

int mx[3 * N];
int spf[3 * N];
bool is_prime[3 * N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree_min[node] += lazy[node];
    segtree_max[node] += lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree_max[node] = max(segtree_max[node * 2 + 1], segtree_max[node * 2 + 2]);
    segtree_min[node] = min(segtree_min[node * 2 + 1], segtree_min[node * 2 + 2]);
}

int getMax(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_max[node];
    }
    int mid = (l + r) / 2;
    return max(getMax(l, mid, lq, rq, 2 * node + 1),
           getMax(mid + 1, r, lq, rq, 2 * node + 2));
}

int getMin(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return M;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree_min[node];
    }
    int mid = (l + r) / 2;
    return min(getMin(l, mid, lq, rq, 2 * node + 1),
           getMin(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree_max[node] = a[l];
        segtree_min[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree_max[node] = max(segtree_max[node * 2 + 1], segtree_max[node * 2 + 2]);
    segtree_min[node] = min(segtree_min[node * 2 + 1], segtree_min[node * 2 + 2]);
}

int main() {
    IOS;
    sieve(3 * N);
    ans[1] = 1;
    for (int i = 2; i < 3 * N; i++) {
        ans[i] = ans[i - 1];
        int x = i;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) {
                e++;
                x /= p;
            }
            if (e > mx[p]) {
                for (int j = mx[p]; j < e; j++) {
                    ans[i] = ans[i] * p % M;
                }
                mx[p] = e;
            }
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, k;
            cin >> l >> r >> k;
            incUpdate(0, 0, n - 1, l, r, k);
        } else if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << ans[getMax(0, n - 1, l, r, 0)] << endl;
        } else {
            int l, r;
            cin >> l >> r;
            cout << ans[getMin(0, n - 1, l, r, 0)] << endl;
        }
    }
    return 0;
}
