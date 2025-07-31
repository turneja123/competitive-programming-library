//https://codeforces.com/contest/1748/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const long long M = 1e9 + 7;

int table_mx[K][N];
int mx[K][N];
int a[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] >= table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mx[k][l] >= table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }
    return b;
}

struct Node {
    int left;
    int right;
    vector<long long> dp;
    vector<long long> pref;
    Node() {
    }
    Node(int m) {
        dp.resize(m + 1, 0);
        pref.resize(m + 1, 0);
        left = -1;
        right = -1;
    }
};

int idx = 0;
Node nodes[N];

int cartesian(int l, int r, int m) {
    if (l > r) {
        return -1;
    }
    int node = idx;
    nodes[idx++] = Node(m);
    int mid = query(l, r);
    nodes[node].left = cartesian(l, mid - 1, m);
    nodes[node].right = cartesian(mid + 1, r, m);
    return node;
}

void dfs(int node, int m) {
    if (nodes[node].left != -1) {
        dfs(nodes[node].left, m);
    }
    if (nodes[node].right != -1) {
        dfs(nodes[node].right, m);
    }
    for (int i = 1; i <= m; i++) {
        nodes[node].dp[i] = (nodes[node].left == -1 ? 1 : nodes[nodes[node].left].pref[i - 1]) * (nodes[node].right == -1 ? 1 : nodes[nodes[node].right].pref[i]) % M;
        nodes[node].pref[i] = (nodes[node].pref[i - 1] + nodes[node].dp[i]) % M;
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(n);
        cartesian(0, n - 1, m);
        dfs(0, m);
        cout << nodes[0].pref[m] << endl;
        idx = 0;
    }

    return 0;
}
