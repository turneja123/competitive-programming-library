//https://atcoder.jp/contests/abc332/tasks/abc332_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const long long M = 998244353;

long long a[N];
long long segtree[2][4 * N];
long long lazy[2][4 * N];
long long setVal[2][4 * N];
bool setValid[2][4 * N];

tuple<int, int, int, int> queries[2 * N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void compose(int parent, int child, int n) {
    if (setValid[n][parent]) {
        setValid[n][child] = 1;
        setVal[n][child] = setVal[n][parent];
        lazy[n][child] = lazy[n][parent];
    } else {
        lazy[n][child] = lazy[n][child] * lazy[n][parent] % M;
    }
}

void apply(int node, int l, int r, int n) {
    if (setValid[n][node]) {
        if (n == 0) {
            segtree[n][node] = setVal[n][node] * (r - l + 1) % M;
        } else {
            segtree[n][node] = modPow(setVal[n][node], r - l + 1);
        }
    }
    if (n == 0) {
        segtree[n][node] = segtree[n][node] * lazy[n][node] % M;
    }
    if (l != r) {
        compose(node, 2 * node + 1, n);
        compose(node, 2 * node + 2, n);
    }
    setValid[n][node] = false;
    lazy[n][node] = 1;
}

void mulUpdate(int node, int l, int r, int lq, int rq, ll add, int n) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[n][node] = lazy[n][node] * add % M;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    mulUpdate(node * 2 + 1, l, mid, lq, rq, add, n);
    mulUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    if (n == 0) {
        segtree[0][node] = (segtree[0][node * 2 + 1] + segtree[0][node * 2 + 2]) % M;
    } else {
        segtree[1][node] = segtree[1][node * 2 + 1] * segtree[1][node * 2 + 2] % M;
    }
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val, int n) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[n][node] = true;
        setVal[n][node] = val;
        lazy[n][node] = 1;
        return;
    }
    apply(node, l, r, n);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val, n);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val, n);
    apply(2 * node + 1, l, mid, n);
    apply(2 * node + 2, mid + 1, r, n);
    if (n == 0) {
        segtree[0][node] = (segtree[0][node * 2 + 1] + segtree[0][node * 2 + 2]) % M;
    } else {
        segtree[1][node] = segtree[1][node * 2 + 1] * segtree[1][node * 2 + 2] % M;
    }
}

long long getProd(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 1;
    }
    apply(node, l, r, 1);
    if (l >= lq && r <= rq) {
        return segtree[1][node] % M;
    }
    int mid = (l + r) / 2;
    return getProd(l, mid, lq, rq, 2 * node + 1) *
           getProd(mid + 1, r, lq, rq, 2 * node + 2) % M;
}

long long getSum(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r, n);
    if (l >= lq && r <= rq) {
        return segtree[n][node] % M;
    }
    int mid = (l + r) / 2;
    return (getSum(l, mid, lq, rq, 2 * node + 1, n) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2, n)) % M;
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    lazy[0][node] = 1;
    segtree[1][node] = 1;
    if (l == r) {

        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    int n, q, t = 0;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        queries[t++] = make_tuple(i, i, a[i], t);
    }
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        queries[t++] = make_tuple(l, r, x, t);
    }
    sort(queries, queries + t);
    build(0, t - 1, 0);
    priority_queue<tuple<int, int, int, int>> pq;
    for (int i = 0, l = 0; i < n; i++) {
        int mx = 0;
        while (pq.size() && -get<0>(pq.top()) < i) {
            int lq = get<1>(pq.top()), rq = -get<0>(pq.top()), x = get<2>(pq.top()), tim = get<3>(pq.top());
            pq.pop();
            long long prob = modPow(rq - lq + 1, M - 2), inv = modPow(rq - lq + 1, M - 2) * (rq - lq) % M;
            setUpdate(0, 0, t - 1, tim, tim, 0, 0);
            setUpdate(0, 0, t - 1, tim, tim, 1, 1);
            if (tim > 0 && inv != 0) {
                mulUpdate(0, 0, t - 1, 0, tim - 1, modPow(inv, M - 2), 0);
            }
        }
        while (l < t && get<0>(queries[l]) == i) {
            int lq = get<0>(queries[l]), rq = get<1>(queries[l]), x = get<2>(queries[l]), tim = get<3>(queries[l]);
            long long prob = modPow(rq - lq + 1, M - 2), inv = modPow(rq - lq + 1, M - 2) * (rq - lq) % M;
            long long ex = (long long)x * prob % M * ((tim == t - 1) ? 1 : getProd(0, t - 1, tim + 1, t - 1, 0)) % M;
            setUpdate(0, 0, t - 1, tim, tim, ex, 0);
            if (inv != 0) {
                setUpdate(0, 0, t - 1, tim, tim, inv, 1);
            }
            if (tim > 0 && inv != 0) {
                mulUpdate(0, 0, t - 1, 0, tim - 1, inv, 0);
            }
            if (lq == rq) {
                mx = max(mx, tim);
            }
            pq.push(make_tuple(-rq, lq, x, tim));
            l++;
        }

        cout << getSum(0, t - 1, mx, t - 1, 0, 0) % M << " ";
    }

    return 0;
}
