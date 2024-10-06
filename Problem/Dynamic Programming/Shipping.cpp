//https://atcoder.jp/contests/abc374/tasks/abc374_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

long long a[N];
long long pref[N];

vector<pair<long long, long long>> dp[N];

int main() {
    IOS;
    int n, k; long long x;
    cin >> n >> k >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
    }
    for (int i = 0; i < n; i++) {
        if (i + 1 <= k) {
            long long cur = a[i] * (i + 1) - pref[i];
            dp[i].push_back(make_pair(cur, a[i]));
        }

        for (int j = i - 1; j >= 0; j--) {
            if (i - j > k) {
                break;
            }
            for (int p = 0; p < dp[j].size(); p++) {
                long long tim = max(dp[j][p].second + x, a[i]);
                long long cur = tim * (i - j) - (pref[i] - pref[j]);
                dp[i].push_back(make_pair(cur + dp[j][p].first, tim));
            }
        }
        vector<pair<long long, long long>> nx;
        sort(dp[i].begin(), dp[i].end());
        long long mn = 1e18;
        for (int p = 0; p < dp[i].size(); p++) {
            mn = min(mn, dp[i][p].second);
            if (dp[i][p].second > mn) {
                continue;
            }
            nx.push_back(dp[i][p]);
        }
        while (nx.size() > 500) {
            nx.pop_back();
        }
        dp[i] = nx;
    }
    long long ans = 1e18;
    for (int p = 0; p < dp[n - 1].size(); p++) {
        ans = min(ans, dp[n - 1][p].first);
    }
    cout << ans;


    return 0;

}
