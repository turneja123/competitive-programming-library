//https://www.spoj.com/problems/EVENFRQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

map<int, long long> mp;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

int a[N];

long long segtree[4 * N];
long long seg_hash[4 * N];
long long setVal[4 * N];
bool setValid[4 * N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node];
        if ((r - l + 1) % 2 == 0) {
            seg_hash[node] = 0;
        } else {
            seg_hash[node] = mp[setVal[node]];
        }
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    seg_hash[node] = seg_hash[node * 2 + 1] ^ seg_hash[node * 2 + 2];
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

long long getHash(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return seg_hash[node];
    }
    int mid = (l + r) / 2;
    return getHash(l, mid, lq, rq, 2 * node + 1) ^
           getHash(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    setVal[node] = 0;
    setValid[node] = 0;
    if (l == r) {
        segtree[node] = a[l];
        seg_hash[node] = mp[a[l]];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    seg_hash[node] = seg_hash[node * 2 + 1] ^ seg_hash[node * 2 + 2];
}


long long gen() {
    long long h = generator() + ((long long)generator() << 30);
    return h;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (mp.find(a[i]) == mp.end()) {
                mp[a[i]] = gen();
            }
        }
        build(0, n - 1, 0);
        cout << "Case " << tt << ":" << endl;
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            if (t == 0) {
                int j; long long x;
                cin >> j >> x;
                j--;
                long long cur = getSum(0, n - 1, j, j, 0);
                x += cur;
                if (mp.find(x) == mp.end()) {
                    mp[x] = gen();
                }
                setUpdate(0, 0, n - 1, j, j, x);
            } else if (t == 1) {
                int l, r; long long x;
                cin >> l >> r >> x;
                l--, r--;
                if (mp.find(x) == mp.end()) {
                    mp[x] = gen();
                }
                setUpdate(0, 0, n - 1, l, r, x);
            } else {
                int l, r;
                cin >> l >> r;
                l--, r--;
                long long ans = getHash(0, n - 1, l, r, 0);
                if (ans == 0) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
        mp.clear();
    }

    return 0;
}
