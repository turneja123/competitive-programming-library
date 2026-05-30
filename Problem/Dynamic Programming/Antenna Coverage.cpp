//https://codeforces.com/contest/1253/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int dp[N];

vector<pair<int, int>> ivals;

int calc(int i, int n) {
    if (i > n) {
        return 0;
    }
    if (dp[i] != -1) {
        return dp[i];
    }
    dp[i] = N;
    for (auto [l, r] : ivals) {
        if (r >= i) {
            int add = max(0, l - i);
            dp[i] = min(dp[i], add + calc(r + add + 1, n));
            dp[i] = min(dp[i], add + max(0, n - (r + add)));
        }
    }
    return dp[i];
}


int main() {
    IOS;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int x, s;
        cin >> x >> s;
        int l = max(1, x - s), r = min(n, x + s);
        ivals.push_back({l, r});
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = -1;
    }
    cout << calc(1, n);
    return 0;
}
