//https://leetcode.com/contest/weekly-contest-411/problems/find-the-largest-palindrome-divisible-by-k/
class Solution {
public:
    int pw[100005];
    pair<int, int> dp[100005][10];

    string largestPalindrome(int n, int k) {
        pw[0] = 1;
        for (int i = 1; i < n; i++) {
            pw[i] = pw[i - 1] * 10 % k;
        }
        for (int i = 0; i < n; i++) {
            for (int m = 0; m < k; m++) {
                dp[i][m] = make_pair(-1, -1);
            }
        }
        int i = 0, l, r;
        if (n % 2 == 1) {
            for (int d = 0; d < 10; d++) {
                dp[0][d * pw[n / 2] % k] = max(dp[0][d * pw[n / 2] % k], make_pair(d, -1));
            }
            l = n / 2, r = n / 2;
        } else {
            for (int d = 0; d < 10; d++) {
                dp[0][d * (pw[n / 2] + pw[n / 2 - 1]) % k] = make_pair(d, -1);
            }
            l = n / 2 - 1, r = n / 2;
        }
        for (i = 1; i < n; i++) {
            l--, r++;
            if (l < 0) {
                break;
            }
            for (int d = 0; d < 10; d++) {
                for (int j = 0; j < k; j++) {
                    if (dp[i - 1][j].first == -1) {
                        continue;
                    }
                    dp[i][(j + d * (pw[r] + pw[l])) % k] = max(dp[i][(j + d * (pw[r] + pw[l])) % k], make_pair(d, dp[i - 1][j].first));
                }
            }
        }
        i--;
        string lans = "", rans = "";
        r = n - 1, l = 0; int m = 0;
        for (int j = i; j >= 0; j--) {
            char cur = '0' + dp[j][m].first;
            lans += cur;
            if (!(n % 2 == 1 && j == 0)) {
                rans += cur;
            }
            m = (m - dp[j][m].first * (pw[r] + pw[l]) + 100 * k) % k;
            l++, r--;
        }
        reverse(rans.begin(), rans.end());
        string ans = lans + rans;
        return ans;
    }
};
