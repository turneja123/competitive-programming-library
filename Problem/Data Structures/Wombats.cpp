//https://dmoj.ca/problem/ioi13p3io
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int B = 20;
const int INF = 2e9;

int n, m, sz;

vector<vector<int>> rows, cols;
vector<vector<int>> opt;

struct Node {
    vector<vector<int>> dp;
    int l; int r;
    Node() {

    }
    Node(int k) {
        dp.resize(m, vector<int>(m));
        l = k, r = k;
        for (int i = 0; i < m; i++) {
            int s = 0;
            for (int j = i; j < m; j++) {
                dp[i][j] = dp[j][i] = s;
                if (j != m - 1) {
                    s += cols[k][j];
                }
            }
        }
    }
};

Node segtree[4 * N];

void combine(Node& node, Node& left, Node &right) {
    for (int i = 0; i < m; i++) {
        for (int j = m - 1; j >= 0; j--) {
            node.dp[i][j] = INF;
            int l = (i == 0 ? 0 : opt[i - 1][j]);
            int r = (j == m - 1 ? m - 1 : opt[i][j + 1]);
            for (int k = l; k <= r; k++) {
                if (node.dp[i][j] > left.dp[i][k] + right.dp[k][j] + rows[left.r][k]) {
                    node.dp[i][j] = left.dp[i][k] + right.dp[k][j] + rows[left.r][k];
                    opt[i][j] = k;
                }
            }
        }
    }
    node.l = left.l;
    node.r = right.r;
    return;
}

void make(Node& node, int k) {
    node = Node(k * B);
    for (int i = k * B + 1; i <= min(n - 1, (k + 1) * B - 1); i++) {
        Node cur(i), aux;
        aux.dp.resize(m, vector<int>(m));
        combine(aux, node, cur);
        node = aux;
    }
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        make(segtree[node], l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    combine(segtree[node], segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {

    if (l == r) {
        make(segtree[node], l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node].dp.resize(m, vector<int>(m));
    combine(segtree[node], segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    cin >> n >> m;
    sz = (n + B - 1) / B;
    opt.resize(m, vector<int>(m));
    cols.resize(n, vector<int>(m - 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 1; j++) {
            cin >> cols[i][j];
        }
    }
    rows.resize(n - 1, vector<int>(m));
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            cin >> rows[i][j];
        }
    }
    build(0, sz - 1, 0);
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, q, w;
            cin >> p >> q >> w;
            cols[p][q] = w;
            update(0, sz - 1, p / B, 0);
        } else if (t == 2) {
            int p, q, w;
            cin >> p >> q >> w;
            rows[p][q] = w;
            update(0, sz - 1, p / B, 0);
        } else {
            int l, r;
            cin >> l >> r;
            cout << segtree[0].dp[l][r] << endl;
        }
    }


    return 0;
}
