//https://codeforces.com/contest/2048/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const long long INF = 2e18;

ll table_mx[K][N];
ll mx[K][N];
ll a[N];
ll b[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] <= table_mx[k - 1][i + (1 << (k - 1))]) {
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
    if (table_mx[k][l] <= table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }
    return b;
}

struct Node {
    int left;
    int right;
    int mid;
    vector<long long> dp;
    Node() {
    }
    Node(int m) {
        dp.resize(m, INF);
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
    nodes[node].mid = mid;
    nodes[node].left = cartesian(l, mid - 1, m);
    nodes[node].right = cartesian(mid + 1, r, m);
    return node;
}

vector<long long> conv(vector<long long> a, vector<long long> b) {
    vector<long long> ans(64, INF);
    for (int i = 0; i < 64; i++) {
        for (int j = 0; i + j < 64; j++) {
            ans[i + j] = min(ans[i + j], max(a[i], b[j]));
        }
    }
    return ans;
}

void dfs(int node) {
    if (nodes[node].left != -1) {
        dfs(nodes[node].left);
    }
    if (nodes[node].right != -1) {
        dfs(nodes[node].right);
    }
    vector<ll> dp(64, 1);
    if (nodes[node].left != -1 && nodes[node].right == -1) {
        dp = nodes[nodes[node].left].dp;
    } else if (nodes[node].right != -1 && nodes[node].left == -1) {
        dp = nodes[nodes[node].right].dp;
    } else if (nodes[node].left != -1) {
        dp = conv(nodes[nodes[node].left].dp, nodes[nodes[node].right].dp);
    }
    for (int i = 0; i < 64; i++) {
        dp[i] = max(dp[i], b[nodes[node].mid]);
    }
    for (int i = 0; i < 63; i++) {
        dp[i + 1] = min(dp[i + 1], (dp[i] + a[nodes[node].mid] - 1) / a[nodes[node].mid]);
    }
    nodes[node].dp = dp;
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(n);
        cartesian(0, n - 1, 64);
        dfs(0);
        int ans = 64;
        for (int i = 0; i < 64; i++) {
            if (nodes[0].dp[i] == 1) {
                ans = i;
                break;
            }
        }
        cout << ans << endl;
        idx = 0;
    }

    return 0;
}
