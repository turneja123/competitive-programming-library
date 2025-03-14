//https://www.spoj.com/problems/IQUERY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 17;
const long long M = 1e9 + 7;

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

struct Node {
    bool sentinel;
    long long prod;
    vector<long long> v;
    Node() {
        sentinel = true;
        prod = 1;
        v.resize(K, 0);
    }
    Node(int x) {
        sentinel = false;
        prod = x + 1;
        v.resize(K, 0);
        for (int i = 0; i < K; i++) {
            int c = (1 << i) & x;
            if (c) {
                v[i]++;
            }
        }
    }
};

Node segtree[4 * N];
long long a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = false;
    node.prod = left.prod * right.prod % M;
    for (int i = 0; i < K; i++) {
        node.v[i] = left.v[i] + right.v[i];
    }

    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel = Node();
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 'U') {
            int j, val;
            cin >> j >> val;
            j--;
            update(0, n - 1, j, val, 0);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node node = query(0, n - 1, l, r, 0);
            if (t == 'M') {
                cout << (node.prod - 1 + M) % M << endl;
            } else {
                long long ans = 0;
                for (int i = 0; i < K; i++) {
                    ans += (long long)(1 << i) * (modPow(2, node.v[i]) - 1) % M;
                }
                cout << ans % M << endl;
            }
        }
    }

    return 0;
}
