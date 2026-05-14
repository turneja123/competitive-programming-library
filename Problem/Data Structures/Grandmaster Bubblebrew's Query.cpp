//https://bubblecup.org/CompetitorsCorner/Problem/GMBQUERY
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 6;

struct Node {
    int dp[1 << K];
    Node() {
        for (int i = 0; i < 1 << K; i++) {
            dp[i] = 0;
        }
    }
    Node(int x, int y) {
        for (int i = 0; i < 1 << K; i++) {
            dp[i] = 0;
        }
        dp[y] = x;
        for (int i = 0; i < 1 << K; i++) {
            for (int j = 0; j < K; j++) {
                int c = (1 << j) & i;
                if (c) {
                    dp[i] = max(dp[i], dp[i ^ (1 << j)]);
                }
            }
        }
    }
};

Node segtree[4 * N];
int a[N];
int mask[N];

Node combine(Node left, Node right) {
    Node node = Node();
    for (int i = 0; i < 1 << K; i++) {
        for (int j = i; 1; j = (j - 1) & i) {
            node.dp[i] = max(node.dp[i], left.dp[j] + right.dp[i ^ j]);
            if (!j) {
                break;
            }
        }
    }
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
        segtree[node] = Node(val, mask[l]);
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
        segtree[node] = Node(a[l], mask[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, k, q;
    cin >> n >> k >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            x--;
            mask[i] |= 1 << x;
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            l--;
            update(0, n - 1, l, r, 0);
        } else {
            l--, r--;
            Node node = query(0, n - 1, l, r, 0);
            cout << node.dp[(1 << K) - 1] << endl;
        }
    }

    return 0;
}
