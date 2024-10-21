//https://codeforces.com/contest/587/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 31;

class Basis {
public:
    vector<int> basis;
    int sz;

    Basis() : basis(vector<int>(K, 0)), sz(0) {}

    vector<int> get_basis() {
        return basis;
    }

    int get_sz() {
        return sz;
    }

    void insert_vector(int a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                sz++;
                return;
            }
            a ^= basis[i];
        }
    }

    void clear_basis() {
        for (int i = 0; i < K; i++) {
            basis[i] = 0;
        }
        sz = 0;
    }

    void merge_bases(Basis a, Basis b) {
        clear_basis();
        vector<int> va = a.get_basis(), vb = b.get_basis();
        for (int v : va) {
            insert_vector(v);
        }
        for (int v : vb) {
            insert_vector(v);
        }
    }
};

int a[N];
int b[N];
int pw[K];
int vals[4 * N];
int lazy[4 * N];
Basis segtree[4 * N];

Basis query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Basis b;
        return b;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    Basis b;
    b.merge_bases(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
    return b;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        a[ind] ^= val;
        segtree[node].clear_basis();
        segtree[node].insert_vector(a[ind]);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    Basis b;
    segtree[node].merge_bases(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void compose(int parent, int child) {
    lazy[child] ^= lazy[parent];
}

void apply(int node, int l, int r) {
    vals[node] ^= lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

int get(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return vals[node];
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        return get(l, mid, ind, 2 * node + 1);
    } else {
        return get(mid + 1, r, ind, 2 * node + 2);
    }
}

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] ^= add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    vals[node] = vals[node * 2 + 1] ^ vals[node * 2 + 2];
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].insert_vector(a[l]);
        vals[node] = b[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node].merge_bases(segtree[2 * node + 1], segtree[2 * node + 2]);
    vals[node] = vals[node * 2 + 1] ^ vals[node * 2 + 2];
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < K; i++) {
        pw[i] = pw[i - 1] * 2;
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (i > 0) {
            a[i] = b[i] ^ b[i - 1];
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            incUpdate(0, 0, n - 1, l, r, k);
            update(0, n - 1, l, k, 0);
            if (r != n - 1) {
                update(0, n - 1, r + 1, k, 0);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (l == r) {
                int x = get(0, n - 1, l, 0);
                if (x > 0) {
                    x = 2;
                } else {
                    x = 1;
                }
                cout << x << endl;
                continue;
            }
            Basis b = query(0, n - 1, l + 1, r, 0);
            b.insert_vector(get(0, n - 1, l, 0));
            cout << pw[b.get_sz()] << endl;
        }
    }


    return 0;
}
