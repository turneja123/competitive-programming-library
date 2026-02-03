//https://evaluator.hsin.hr/events/coci26_4/tasks/HONI252648tjelesni/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];

struct Node {
    int lazy;
    int has;
    int ct[2];
    int sentinel;

    Node() {
        sentinel = 1;
        lazy = 0;
    }
    Node(int x)  {
        sentinel = 0;
        lazy = 0;
        ct[0] = 0, ct[1] = 0;
        if (x == 2) {
            has = 1;
            x = 0;
        } else {
            has = 0;
        }
        ct[x]++;
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
    node.ct[0] = left.ct[0] + right.ct[0];
    node.ct[1] = left.ct[1] + right.ct[1];
    node.has = left.has | right.has;
    return node;
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy == 0) {
        return;
    }
    //00000 11111 01010 10101
    if (segtree[node].lazy == 1) {
        segtree[node].ct[0] = r - l + 1;
        segtree[node].ct[1] = 0;
    } else if (segtree[node].lazy == 2) {
        segtree[node].ct[0] = 0;
        segtree[node].ct[1] = r - l + 1;
    } else if (segtree[node].lazy == 3) {
        segtree[node].ct[0] = (r - l + 2) / 2;
        segtree[node].ct[1] = (r - l + 1) / 2;
    } else {
        segtree[node].ct[0] = (r - l + 1) / 2;
        segtree[node].ct[1] = (r - l + 2) / 2;
    }
    if (l != r) {
        int mid = (l + r) / 2;
        if (segtree[node].lazy == 1) {
            segtree[2 * node + 1].lazy = 1;
            segtree[2 * node + 2].lazy = 1;
        } else if (segtree[node].lazy == 2) {
            segtree[2 * node + 1].lazy = 2;
            segtree[2 * node + 2].lazy = 2;
        } else if (segtree[node].lazy == 3) {
            segtree[2 * node + 1].lazy = 3;
            if ((mid + 1) % 2 == l % 2) {
                segtree[2 * node + 2].lazy = 3;
            } else {
                segtree[2 * node + 2].lazy = 4;
            }
        } else {
            segtree[2 * node + 1].lazy = 4;
            if ((mid + 1) % 2 == l % 2) {
                segtree[2 * node + 2].lazy = 4;
            } else {
                segtree[2 * node + 2].lazy = 3;
            }
        }

    }
    segtree[node].lazy = 0;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r || l > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = val;
        if (val == 3 && (l % 2 != lq % 2)) {
            segtree[node].lazy = 4;
        }
        if (val == 4 && (l % 2 != lq % 2)) {
            segtree[node].lazy = 3;
        }
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void setPos(int node, int l, int r, int ind, int val) {

    apply(node, l, r);
    if (l == r) {
        segtree[node].has = val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        setPos(2 * node + 1, l, mid, ind, val);
    } else {
        setPos(2 * node + 2, mid + 1, r, ind, val);
    }

    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node getNode(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel;
        return sentinel;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(getNode(l, mid, lq, rq, 2 * node + 1), getNode(mid + 1, r, lq, rq, 2 * node + 2));
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
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q, m;
    cin >> n >> q >> m;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == m) {
            a[i] = 2;
            pos = i;
        } else if (a[i] < m) {
            a[i] = 0;
        } else {
            a[i] = 1;
        }

    }
    build(0, n - 1, 0);
    setPos(0, 0, n - 1, pos, 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        Node node = getNode(0, n - 1, l, r, 0);

        if (node.ct[0] == 0) {
            continue;
        }

        int z = pos >= l && pos <= r;
        if (z) {
            setPos(0, 0, n - 1, pos, 0);
        }
        if (node.ct[0] > node.ct[1]) {
            int mid = l + 2 * node.ct[1] - 1;

            setUpdate(0, 0, n - 1, l, mid, 3);
            setUpdate(0, 0, n - 1, mid + 1, r, 1);
            if (z) {
                pos = min(r, mid + 2);
            }
        } else {
            int mid = l + 2 * node.ct[0] - 2;
            if (node.has) {
                setPos(0, 0, n - 1, pos, 0);
            }
            setUpdate(0, 0, n - 1, l, mid, 3);
            setUpdate(0, 0, n - 1, mid + 1, r, 2);
            if (node.has) {
                pos = mid;
            }
        }
        if (z) {
            setPos(0, 0, n - 1, pos, 1);
        }

    }
    cout << pos + 1;

    return 0;
}
