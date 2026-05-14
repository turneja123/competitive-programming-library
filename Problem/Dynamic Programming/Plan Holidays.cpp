//https://atcoder.jp/contests/abc456/tasks/abc456_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


const long long INF = 1e18;

struct Node {
    ll dp[2][2];
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(long long x) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                dp[i][j] = -INF;
            }
        }
        dp[0][0] = 0;
        dp[1][1] = x;
        sentinel = 0;
    }
};

Node segtree[4 * N];
long long a[N];
ll pref[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            node.dp[i][j] = -INF;
            for (int k = 0; k < 2; k++) {
                node.dp[i][j] = max(node.dp[i][j], left.dp[i][k] + right.dp[k ^ 1][j]);
            }
            node.dp[i][j] = max(node.dp[i][j], left.dp[i][0] + right.dp[0][j]);
            if (node.dp[i][j] < 0) {
                node.dp[i][j] = -INF;
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
    int t;
    cin >> t;
    while (t--) {
        int n, K;
        cin >> n >> K;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        }
        ll ans = INF;
        build(0, n - 1, 0);
        for (int k = K; k <= min(n, K + 3); k++) {
            for (int i = k - 1; i < n; i++) {
                Node node = query(0, n - 1, i - k + 1, i, 0);
                ans = min(ans, pref[i] - (i - k == -1 ? 0 : pref[i - k]) - max(0ll, node.dp[0][0]));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
