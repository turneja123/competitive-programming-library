//https://atcoder.jp/contests/abc425/tasks/abc425_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int K = 30;
const int MAX = 1e7 + 5;

struct Node {
    int left;
    int right;
    int sum;
    Node() : left(-1), right(-1), sum(0) {}
};

Node nodes[MAX];
int idx = 0;
int dp[K][2];
ll ans = 0;

int ct(int n, vector<int> &f) {
    vector<int> d(K, 0);
    for (int i = 0; i < K; i++) {
        int c = (1 << i) & n;
        d[i] = c > 0;
    }
    dp[K - 1][0] = 0, dp[K - 1][1] = 0;
    if (d[K - 1] == 0) {
        if (f[K - 1] == -1 || f[K - 1] == 0) {
            dp[K - 1][1] += 1;
        }
    } else {
        if (f[K - 1] == -1 || f[K - 1] == 0) {
            dp[K - 1][0] += 1;
        }
        if (f[K - 1] == -1 || f[K - 1] == 1) {
            dp[K - 1][1] += 1;
        }
    }
    for (int i = K - 2; i >= 0; i--) {
        dp[i][0] = 0, dp[i][1] = 0;
        if (d[i] == 0) {
            if (f[i] == -1 || f[i] == 0) {
                dp[i][0] += dp[i + 1][0];
                dp[i][1] += dp[i + 1][1];
            }
            if (f[i] == -1 || f[i] == 1) {
                dp[i][0] += dp[i + 1][0];
            }
        } else {
            if (f[i] == -1 || f[i] == 0) {
                dp[i][0] += dp[i + 1][0] + dp[i + 1][1];
            }
            if (f[i] == -1 || f[i] == 1) {
                dp[i][0] += dp[i + 1][0];
                dp[i][1] += dp[i + 1][1];
            }
        }
    }
    return (dp[0][0] + dp[0][1]);
}


void calc(int node, int d, vector<int> pref, int m) {
    if (d == -1 || ct(m, pref) == 0) {
        return;
    }
    if (nodes[nodes[node].left].sum == 0) {
        pref[d] = 0;
        ans += (ll)ct(m, pref) * (1 << d);
        pref[d] = -1;
        calc(nodes[node].right, d - 1, pref, m);
    } else if (nodes[nodes[node].right].sum == 0) {
        pref[d] = 1;
        ans += (ll)ct(m, pref) * (1 << d);
        pref[d] = -1;
        calc(nodes[node].left, d - 1, pref, m);
    } else {
        pref[d] = 0;
        calc(nodes[node].left, d - 1, pref, m);
        pref[d] = 1;
        calc(nodes[node].right, d - 1, pref, m);
    }
    return;
}

void add(int node, int d, int val) {
    nodes[node].sum++;
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val);
        return;
    }
}


int main() {
    IOS;
    nodes[idx++] = Node();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        add(0, K - 1, a);
    }
    vector<int> pref(K, -1);
    calc(0, K - 1, pref, m - 1);
    cout << ans;

    return 0;
}
