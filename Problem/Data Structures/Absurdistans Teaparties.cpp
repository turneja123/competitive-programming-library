//https://www.spoj.com/problems/TEAPARTY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct Node {
    long long sum;
    long long lazy;
    Node() {
        lazy = 0;
    }
    Node(long long x) : sum(x), lazy(0) {}
};

int a[N];
vector<int> l_a, r_a;
vector<Node> l_segtree, r_segtree;

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = max(left.sum, right.sum);
    return node;
}

void compose(int parent, int child, vector<Node> &segtree) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r, vector<Node> &segtree) {
    segtree[node].sum += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1, segtree);
        compose(node, 2 * node + 2, segtree);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add, vector<Node> &segtree) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r, segtree);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, segtree);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, segtree);
    apply(2 * node + 1, l, mid, segtree);
    apply(2 * node + 2, mid + 1, r, segtree);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

long long getMax(int l, int r, int lq, int rq, int node, vector<Node> &segtree) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r, segtree);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return max(getMax(l, mid, lq, rq, 2 * node + 1, segtree), getMax(mid + 1, r, lq, rq, 2 * node + 2, segtree));
}

void build(int l, int r, int node, vector<int> &b, vector<Node> &segtree) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l] + b[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1, b, segtree);
    build(mid + 1, r, node * 2 + 2, b, segtree);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q, c;
    cin >> n >> q >> c;
    l_a.resize(n);
    r_a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        l_a[i] = i * c;
        r_a[i] = (n - 1 - i) * c;
    }
    l_segtree.resize(4 * n);
    r_segtree.resize(4 * n);
    build(0, n - 1, 0, l_a, l_segtree);
    build(0, n - 1, 0, r_a, r_segtree);
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "change") {
            int j, v;
            cin >> j >> v;
            long long diff = v - a[j];
            incUpdate(0, 0, n - 1, j, j, diff, l_segtree);
            incUpdate(0, 0, n - 1, j, j, diff, r_segtree);
            a[j] = v;
        } else if (s == "accident") {
            int l, r, v; char d;
            cin >> l >> r >> v >> d;
            incUpdate(0, 0, n - 1, l, r, v, ((d == 'l') ? l_segtree : r_segtree));
        } else {
            int j, l, r, t;
            cin >> j >> l >> r >> t;
            long long mx = 0;
            if (l < j) {
                long long cur = getMax(0, n - 1, l, min(r, j - 1), 0, r_segtree) - (n - 1 - j) * c;
                mx = max(mx, cur);
            }
            if (r > j) {
                long long cur = getMax(0, n - 1, max(j + 1, l), r, 0, l_segtree) - j * c;
                mx = max(mx, cur);
            }
            cout << t - mx << endl;

        }
    }
    return 0;
}
