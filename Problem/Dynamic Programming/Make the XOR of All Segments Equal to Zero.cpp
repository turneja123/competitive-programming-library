//https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/description/
const int N = 2005;
const int MAX = 1024;
class Solution {
public:
    int dp[N][MAX];
    int freq[N][MAX];
    int ct[N];
    int mn[N];
    vector<int> v[N];

    int minChanges(vector<int>& a, int k) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j += k) {
                ct[i]++;
                freq[i][a[j]]++;
                if (freq[i][a[j]] == 1) {
                    v[i].push_back(a[j]);
                }
            }
        }
        for (int i = 0; i < k; i++) {
            mn[i] = N;
            if (i == 0) {
                for (int j = 0; j < MAX; j++) {
                    dp[i][j] = ct[i] - freq[i][j];
                    mn[i] = min(mn[i], dp[i][j]);
                }
            } else {
                for (int j = 0; j < MAX; j++) {
                    dp[i][j] = N;
                    for (int x : v[i]) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j ^ x] + ct[i] - freq[i][x]);
                    }
                    dp[i][j] = min(dp[i][j], mn[i - 1] + ct[i]);
                    mn[i] = min(mn[i], dp[i][j]);
                }
            }
        }
        return dp[k - 1][0];
    }
};
