//https://atcoder.jp/contests/abc345/tasks/abc345_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<long long, int>> dp[N];

void add(int i, int c, long long v) {
    if (dp[i].size() == 0) {
        dp[i].push_back(make_pair(v, c));
        return;
    }
    if (dp[i][0].second == c) {
        dp[i][0].first = max(dp[i][0].first, v);
    } else if (dp[i].size() > 1 && dp[i][1].second == c) {
        dp[i][1].first = max(dp[i][1].first, v);
    } else {
        dp[i].push_back(make_pair(v, c));
    }
    sort(dp[i].begin(), dp[i].end());
    if (dp[i].size() > 2) {
        dp[i].erase(dp[i].begin());
    }
    return;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    long long ans = -1;
    if (k == n) {
        ans = 0;
    }
    for (int i = 1; i <= n; i++) {
        int c, v;
        cin >> c >> v;
        vector<pair<int, long long>> upd;
        for (int j = 0; j <= min(i - 1, k); j++) {
            if (dp[i - j - 1].size()) {
                int p = dp[i - j - 1].size() - 1;
                long long best = -1;
                if (dp[i - j - 1][p].second == c) {
                    p--;
                    if (p >= 0) {
                        best = max(best, dp[i - j - 1][p].first);
                    }
                } else {
                    best = max(best, dp[i - j - 1][p].first);
                }
                if (best != -1) {
                    upd.push_back(make_pair(i - j, best + v));
                }
            }
        }
        for (auto [j, v] : upd) {
            add(j, c, v);
            if (i - j + n - i == k) {
                ans = max(ans, v);
            }
        }
        if (i - 1 <= k) {
            add(1, c, v);
            if (n - 1 == k) {
                ans = max(ans, (long long)v);
            }
        }
    }
    cout << ans;
    return 0;
}
