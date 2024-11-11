//https://leetcode.com/contest/weekly-contest-423/problems/sum-of-good-subsequences/
const int M = 1e9 + 7;
const int N = 1e5 + 5;
class Solution {
public:
    pair<long long, long long> dp[N];
    bool seen[N];

    int sumOfGoodSubsequences(vector<int>& a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            if (a[i] != 0) {
                dp[a[i]].first = (dp[a[i]].first + dp[a[i] - 1].first) % M;
                dp[a[i]].second = (dp[a[i]].second + dp[a[i] - 1].first * a[i] + dp[a[i] - 1].second) % M;
            }
            dp[a[i]].first = (dp[a[i]].first + dp[a[i] + 1].first) % M;
            dp[a[i]].second = (dp[a[i]].second + dp[a[i] + 1].first * a[i] + dp[a[i] + 1].second) % M;
            dp[a[i]].first = (dp[a[i]].first + 1) % M;
            dp[a[i]].second = (dp[a[i]].second + a[i]) % M;
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (!seen[a[i]]) {
                seen[a[i]] = true;
                ans += dp[a[i]].second;
            }
        }
        return ans % M;
    }
};
