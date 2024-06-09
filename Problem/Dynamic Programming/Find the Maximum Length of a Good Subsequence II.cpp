//https://leetcode.com/contest/biweekly-contest-132/problems/find-the-maximum-length-of-a-good-subsequence-ii/
class Solution {
public:
    int dp[5005][52];
    int dp_next[5005][52];
    multiset<int> mx[52];

    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        set<int> st;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            st.insert(nums[i]);
        }
        int j = 0, m = st.size();
        for (int x : st) {
            mp[x] = j++;
        }
        int ans = 1;
        for (int i = 0; i < n; i++) {
            int pos = mp[nums[i]];
            dp_next[pos][0] = 1;
            for (int j = 0; j <= k; j++) {
                mx[j].erase(mx[j].find(dp[pos][j]));
                dp_next[pos][j] = max(dp_next[pos][j], *mx[j].rbegin() + 1);
                if (j != 0 && dp[pos][j - 1] != 0) {
                    dp_next[pos][j] = max(dp_next[pos][j], dp[pos][j - 1] + 1);
                }
                mx[j].insert(dp[pos][j]);
            }

            for (int j = 0; j <= k; j++) {
                mx[j].erase(mx[j].find(dp[pos][j]));
                mx[j].insert(dp_next[pos][j]);
                dp[pos][j] = dp_next[pos][j];
                dp_next[pos][j] = 0;
                ans = max(ans, dp[pos][j]);

            }
        }
        return ans;


    }
};
