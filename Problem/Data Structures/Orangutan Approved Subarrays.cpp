//https://codeforces.com/contest/2030/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;

int a[N];
int last[N];
int ans[N];

struct Node {
    int val;
    int pos;
    Node() {
        val = N;
        pos = -1;
    }
    Node(int _val, int _pos) {
        val = _val;
        pos = _pos;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val < right.val) {
        node.val = left.val;
        node.pos = left.pos;
    } else {
        node.val = right.val;
        node.pos = right.pos;
    }
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel;
        return sentinel;
    }
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val, l);
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
    if (l == r) {
        segtree[node] = Node();
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int table[K][N];

void build_table(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = ans[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query_table(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            last[a[i]] = -1;
        }
        int l = 0;
        build(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            int x = a[i];
            if (i != 0) {
                while (1) {
                    Node node = query(0, n - 1, last[a[i]] + 1, i - 1, 0);
                    if (node.val > last[a[i]]) {
                        break;
                    }
                    l = max(l, node.val + 1);
                    update(0, n - 1, node.pos, N, 0);
                }
            }
            while (i < n && a[i] == x) {
                update(0, n - 1, i, last[a[i]], 0);
                ans[i] = l;
                i++;
            }
            i--;
            last[a[i]] = i;
        }
        build_table(n);
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (query_table(l, r) <= l) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
