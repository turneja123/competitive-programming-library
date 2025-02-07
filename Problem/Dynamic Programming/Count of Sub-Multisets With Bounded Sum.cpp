//https://leetcode.com/contest/biweekly-contest-115/problems/count-of-sub-multisets-with-bounded-sum/
const int N = 2e4 + 5;
const long long M = 1e9 + 7;
class Solution {
public:
    long long dp[N];

    int countSubMultisets(vector<int>& nums, int l, int r) {
        sort(nums.begin(), nums.end());
        vector<pair<int, int>> a;
        int last = nums[0], j = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == last) {
                j++;
            } else {
                a.push_back(make_pair(last, j));
                last = nums[i];
                j = 1;
            }
        }
        a.push_back(make_pair(last, j));
        dp[0] = 1;
        for (int i = 0; i < a.size(); i++) {
            int n = a[i].first;
            if (n == 0) {
                dp[0] = a[i].second + 1;
                continue;
            }
            vector<long long> pref[n];
            for (int j = 0; j <= r; j++) {
                if (pref[j % n].size() == 0) {
                    pref[j % n].push_back(dp[j]);
                } else {
                    pref[j % n].push_back((dp[j] + pref[j % n].back()) % M);
                }
            }
            int ct = a[i].second;
            for (int j = n; j <= r; j++) {
                int m = j % n;
                int rt = j / n;
                int lf = max(0, rt - ct);
                dp[j] = (dp[j] + pref[m][rt - 1] - (lf == 0 ? 0 : pref[m][lf - 1]) + M) % M;
            }
        }
        long long ans = 0;
        for (int i = l; i <= r; i++) {
            ans = (ans + dp[i]) % M;
        }
        return ans;
    }
};
