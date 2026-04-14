//https://www.spoj.com/problems/HILO/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int d[N];

struct Node {
    int ans;
    int l;
    int r;
    int sentinel;

    Node() {
        sentinel = 1;
    }
    Node(int x) {
        sentinel = 0;
        l = x;
        r = x;
        ans = 0;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = 0;
    node.ans = left.ans + right.ans + (left.r != right.l);
    node.l = left.l;
    node.r = right.r;

    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
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
        if (val == 0) {
            segtree[node] = Node();
            return;
        }
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
        if (d[l] == 0) {
            segtree[node] = Node();
            return;
        }
        segtree[node] = Node(d[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    while (1) {
        int n, q;
        cin >> n >> q;
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i != 0) {
                d[i] = (a[i] < a[i - 1] ? 1 : -1);
            }
            if (i != 0 && a[i] == a[i - 1]) {
                d[i] = 0;
            }
        }
        build(0, n - 1, 0);
        for (int i = 0; i < q; i++) {
            char c;
            cin >> c;
            if (c == 'q') {
                int l, r;
                cin >> l >> r;
                l--, r--;
                if (l == r) {
                    cout << 1 << endl;
                    continue;
                }
                Node node = query(0, n - 1, l + 1, r, 0);
                if (node.sentinel) {
                    cout << 1 << endl;
                    continue;
                }
                cout << 2 + node.ans << endl;
            } else {
                int j, x;
                cin >> j >> x;
                j--;
                a[j] = x;
                if (j != 0) {
                    d[j] = (a[j] < a[j - 1] ? 1 : -1);
                    if (a[j] == a[j - 1]) {
                        d[j] = 0;
                    }
                    update(0, n - 1, j, d[j], 0);
                }
                if (j != n - 1) {
                    d[j + 1] = (a[j + 1] < a[j] ? 1 : -1);
                    if (a[j + 1] == a[j]) {
                        d[j + 1] = 0;
                    }
                    update(0, n - 1, j + 1, d[j + 1], 0);
                }
            }
        }
    }

    return 0;
}
