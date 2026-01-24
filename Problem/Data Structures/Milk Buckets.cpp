//https://usaco.org/index.php?page=viewproblem2&cpid=1546
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    int mx;
    int dist;
    int ind;
    int lazy;
    Node() {
        mx = -1;
        dist = -1;
        lazy = 0;
        ind = 0;
    }
    Node(int _mx, int _dist, int _ind) {
        mx = _mx;
        dist = _dist;
        ind = _ind;
        lazy = 0;
    }
    bool operator < (Node &a) const {
        if (mx != a.mx) {
            return mx < a.mx;
        }
        return dist > a.dist;
    }
};

struct Segtree {
    vector<Node> segtree;

    Segtree(int n) {
        segtree.resize(4 * n);
    }

    Node combine(Node left, Node right) {
        Node node = Node();
        if (right < left) {
            node.mx = left.mx;
            node.dist = left.dist;
            node.ind = left.ind;
        } else {
            node.mx = right.mx;
            node.dist = right.dist;
            node.ind = right.ind;
        }
        return node;
    }

    void apply(int node, int l, int r) {
        segtree[node].dist += segtree[node].lazy;
        if (l != r) {
            segtree[2 * node + 1].lazy += segtree[node].lazy;
            segtree[2 * node + 2].lazy += segtree[node].lazy;
        }
        segtree[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int add) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazy += add;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, lq, rq, add);
        incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void setUpdate(int node, int l, int r, int ind) {
        if (l == r) {
            segtree[node].mx = -1;
            segtree[node].lazy = 0;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        if (ind <= mid) {
            setUpdate(node * 2 + 1, l, mid, ind);
        } else {
            setUpdate(node * 2 + 2, mid + 1, r, ind);
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

    void build(int l, int r, int node, vector<pair<int, int>> &a) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = Node(a[l].first, a[l].second, l);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1, a);
        build(mid + 1, r, node * 2 + 2, a);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

};


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<pair<int, int>> lf(n), rt(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            lf[i] = {a[i], i};
            rt[i] = {a[i], n - 1 - i};
        }
        Segtree L(n), R(n);
        L.build(0, n - 1, 0, lf);
        R.build(0, n - 1, 0, rt);
        ll ans = 0;
        for (int i = 0; i < n - 2; i++) {
            Node l = L.getNode(0, n - 1, 0, n - 1, 0);
            Node r = R.getNode(0, n - 1, 0, n - 1, 0);
            int ind;
            if (r < l) {
                ans += l.dist;
                ind = l.ind;
            } else {
                ans += r.dist;
                ind = r.ind;
            }
            L.incUpdate(0, 0, n - 1, ind, n - 1, -1);
            R.incUpdate(0, 0, n - 1, 0, ind, -1);

            L.setUpdate(0, 0, n - 1, ind);
            R.setUpdate(0, 0, n - 1, ind);

        }
        cout << ans << endl;
    }

    return 0;
}
