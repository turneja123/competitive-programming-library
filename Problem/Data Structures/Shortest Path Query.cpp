//https://atcoder.jp/contests/abc429/tasks/abc429_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

struct Node {
    int dp[3][3];

    Node() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][j] = INF;
            }
        }
    }
    Node(char x, char y, char z) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][j] = INF;
            }
        }
        if (x == '.') {
            dp[0][0] = 0;
            if (y == '.') {
                dp[0][1] = 1;
                dp[1][0] = 1;
                if (z == '.') {
                    dp[0][2] = 2;
                    dp[2][0] = 2;
                }
            }
        }
        if (y == '.') {
            dp[1][1] = 0;
            if (z == '.') {
                dp[1][2] = 1;
                dp[2][1] = 1;
            }
        }
        if (z == '.') {
            dp[2][2] = 0;
        }
    }
};

Node segtree[4 * N];
string s[3];

Node combine(Node left, Node right) {
    Node node = Node();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                node.dp[i][j] = min(node.dp[i][j], left.dp[i][k] + right.dp[k][j] + 1);
            }
        }
    }
    return node;
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = Node(s[0][ind], s[1][ind], s[2][ind]);
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
        segtree[node] = Node(s[0][l], s[1][l], s[2][l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int n;
    cin >> n;
    cin >> s[0] >> s[1] >> s[2];
    build(0, n - 1, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (s[x][y] == '#') {
            s[x][y] = '.';
        } else {
            s[x][y] = '#';
        }
        update(0, n - 1, y, 0);
        int ans = segtree[0].dp[0][2];
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << endl;
    }

    return 0;
}
