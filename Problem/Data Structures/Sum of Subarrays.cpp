//https://atcoder.jp/contests/abc423/tasks/abc423_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int n;

struct Node {
    int l;
    int r;
    ll falling;
    ll rising;
    ll sum_base;
    ll sum;

    Node() {

    }
    Node(ll x, int j) {
        l = j, r = j;
        rising = x * (j + 1);
        falling = x * (n - j);
        sum_base = x;
        sum = x;
    }
};

ll a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    if (left.l == -1) {
        return right;
    }
    if (right.l == -1) {
        return left;
    }
    Node node = Node();
    node.l = left.l;
    node.r = right.r;
    node.falling = left.falling + right.falling;
    node.rising = left.rising + right.rising;
    node.sum_base = left.sum_base + right.sum_base;
    node.sum = left.sum + right.sum;
    node.sum += (left.rising - left.l * left.sum_base) * (right.r - right.l + 1);
    node.sum += (right.falling - (n - right.r - 1) * right.sum_base) * (left.r - left.l + 1);
    return node;
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

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel(-1, -1);
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l], l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << query(0, n - 1, l, r, 0).sum << endl;
    }

    return 0;
}
