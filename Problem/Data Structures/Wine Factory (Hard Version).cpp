//https://codeforces.com/contest/1919/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll INF = 1e18;

struct Node {
    ll dp[2][2];
    ll z;
    Node() {
        dp[0][0] = INF;
        dp[0][1] = INF;
        dp[1][0] = INF;
        dp[1][1] = INF;
    }
    Node(ll a, ll b, ll Z) {
        z = Z;
        dp[0][1] = INF;
        dp[1][0] = INF;
        dp[0][0] = a;
        dp[1][1] = b;
    }
};

Node segtree[4 * N];
ll a[N];
ll b[N];
ll z[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.z = right.z;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                for (int p = 0; p < 2; p++) {
                    node.dp[i][p] = min(node.dp[i][p], left.dp[i][j] + right.dp[k][p] + (j == 1 && k == 0 ? left.z : 0));
                }
            }
        }
    }
    return node;
}


void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = Node(a[l], b[l], z[l]);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l], b[l], z[l]);
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
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> z[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int p; ll x, y, Z;
        cin >> p >> x >> y >> Z;
        p--;
        a[p] = x, b[p] = y, z[p] = Z;
        update(0, n - 1, p, 0);
        cout << min({segtree[0].dp[0][0], segtree[0].dp[0][1], segtree[0].dp[1][0], segtree[0].dp[1][1]}) << endl;
    }
    return 0;
}
