//https://dmoj.ca/problem/noiwc09p1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 2e9;

int a[6][N];

inline void upd(int &x, int y) {
    x ^= (x ^ y) & -(x > y);
}

struct Node {
    int dp[6][6];
    int dp_l[6][6];
    int dp_r[6][6];
    int sentinel;

    Node() {
        sentinel = 1;
        for (int i = 0; i < 6; i++) {
            for (int j = i; j < 6; j++) {
                dp[i][j] = dp[j][i] = dp_l[i][j] = dp_l[j][i] = dp_r[i][j] = dp_r[j][i] = INF;
            }
        }
    }
    Node(int r) {
        sentinel = 0;
        for (int i = 0; i < 6; i++) {
            int s = 0;
            for (int j = i; j < 6; j++) {
                s += a[j][r];
                dp[i][j] = dp[j][i] = dp_l[i][j] = dp_l[j][i] = dp_r[i][j] = dp_r[j][i] = s;
            }
        }
    }
};

Node segtree[4 * N];
string s[3];

int tmp_l[6][6];
int tmp_r[6][6];

int L[6][6];
int R[6][6];

Node combine(const Node& left, const Node &right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node = Node();
    node.sentinel = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            tmp_l[i][j] = INF;
            tmp_r[i][j] = INF;
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                upd(tmp_l[i][j], left.dp[i][k] + right.dp_l[k][j]);
                upd(tmp_r[i][j], left.dp_r[i][k] + right.dp[k][j]);
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 6; k++) {
                upd(node.dp_l[i][j], left.dp_l[i][j]);
                upd(node.dp_l[i][j], tmp_l[i][k] + left.dp[j][k]);
                upd(node.dp_r[i][j], right.dp_r[i][j]);
                upd(node.dp_r[i][j], tmp_r[k][i] + right.dp[k][j]);
                upd(node.dp[i][j], left.dp[i][k] + right.dp[k][j]);
                upd(node.dp[i][j], tmp_l[i][k] + tmp_r[k][j]);
            }
        }
    }
    return node;
}

void update(int l, int r, int ind, int x, int val, int node) {
    if (l == r) {
        a[x][l] = val;
        segtree[node] = Node(l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, x, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, x, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node query(int l, int r, int s, int t, int node) {
    if (l <= s && t <= r) {
        return segtree[node];
    }
    int mid = (s + t) / 2;
    if (l <= mid && r > mid) {
        return combine(query(l, r, s, mid, 2 * node + 1), query(l, r, mid + 1, t, 2 * node + 2));
    }
    if (r > mid) {
        return query(l, r, mid + 1, t, 2 * node + 2);
    }
    return query(l, r, s, mid, 2 * node + 1);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(l);
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
    for (int i = 0; i < 6; i++) {
        a[i][0] = 10005;
        a[i][n + 1] = 10005;
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    build(0, n + 1, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y, c;
            cin >> x >> y >> c;
            x--;
            update(0, n + 1, y, x, c, 0);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, x2--;
            if (y1 > y2) {
                swap(y1, y2);
                swap(x1, x2);
            }
            Node mid = query(y1, y2, 0, n + 1, 0);
            int ans = mid.dp[x1][x2];

            Node left = query(0, y1, 0, n + 1, 0), right = query(y1, n + 1, 0, n + 1, 0);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    L[i][j] = left.dp_r[i][j];
                    upd(L[i][j], right.dp_l[i][j]);
                    for (int k = 0; k < 6; k++) {
                        upd(L[i][j], left.dp_r[i][k] + right.dp_l[k][j] - a[k][y1]);
                        upd(L[i][j], left.dp_r[k][j] + right.dp_l[i][k] - a[k][y1]);
                    }
                }
            }

            Node last = query(y2, n + 1, 0, n + 1, 0);
            right = query(0, y2, 0, n + 1, 0);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    R[i][j] = right.dp_r[i][j];
                    upd(R[i][j], last.dp_l[i][j]);
                    for (int k = 0; k < 6; k++) {
                        upd(R[i][j], right.dp_r[i][k] + last.dp_l[k][j] - a[k][y2]);
                        upd(R[i][j], right.dp_r[k][j] + last.dp_l[i][k] - a[k][y2]);
                    }
                }
            }

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    upd(ans, L[x1][i] + mid.dp[i][j] + R[j][x2] - a[i][y1] - a[j][y2]);
                }
            }
            cout << ans << endl;
        }
    }

    return 0;
}
