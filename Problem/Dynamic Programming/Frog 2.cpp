//https://atcoder.jp/contests/dp/tasks/dp_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 2e9;

int dp[N];
multiset<int> st[N];

struct Node {
    int l;
    int r;
    Node() {}
    Node(int x, int ind) : l(x - ind), r(x + ind) {}
};

Node segtree[4 * N];
int a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.l = min(left.l, right.l);
    node.r = min(left.r, right.r);
    return node;
}

int query(int l, int r, int lq, int rq, int node, int f) {
    if (l > rq || r < lq) {
        return INF;
    }

    if (lq <= l && rq >= r) {
        if (f == 0) {
            return segtree[node].l;
        }
        return segtree[node].r;
    }

    int mid = (l + r) / 2;
    return min(query(l, mid, lq, rq, 2 * node + 1, f), query(mid + 1, r, lq, rq, 2 * node + 2, f));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val, ind);
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
        segtree[node] = Node(INF, 0);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, N - 1, 0);
    dp[0] = 0;
    st[a[0]].insert(0);
    update(0, N - 1, a[0], 0, 0);
    for (int i = 1, l = 0; i < n; i++) {
        while (i - l > k) {
            st[a[l]].erase(st[a[l]].find(dp[l]));
            if (st[a[l]].empty()) {
                update(0, N - 1, a[l], INF, 0);
            } else {
                update(0, N - 1, a[l], *st[a[l]].begin(), 0);
            }
            l++;
        }
        dp[i] = min(a[i] + query(0, N - 1, 0, a[i], 0, 0), query(0, N - 1, a[i], N - 1, 0, 1) - a[i]);
        st[a[i]].insert(dp[i]);
        update(0, N - 1, a[i], *st[a[i]].begin(), 0);
    }
    cout << dp[n - 1];
    return 0;
}
