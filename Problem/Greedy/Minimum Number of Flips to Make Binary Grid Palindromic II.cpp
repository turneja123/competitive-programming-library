//https://leetcode.com/contest/biweekly-contest-136/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/
class Solution {
public:
    int minFlips(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int ans = 0, ct = 0, half = 0;
        for (int i = 0; i < n / 2 + n % 2; i++) {
            for (int j = 0; j < m / 2 + m % 2; j++) {
                if (n % 2 == 1 && m % 2 == 1 && i == n / 2 && j == m / 2) {
                    ans += a[i][j];
                    continue;
                }
                if (n % 2 == 1 && i == n / 2) {
                    if (a[i][j] == 1 && a[i][m - 1 - j] == 1) {
                        ct = (ct + 2) % 4;
                    } else if (!(a[i][j] == 0 && a[i][m - 1 - j] == 0)) {
                        half++;
                    }
                    continue;
                }
                if (m % 2 == 1 && j == m / 2) {
                    if (a[i][j] == 1 && a[n - 1 - i][j] == 1) {
                        ct = (ct + 2) % 4;
                    } else if (!(a[i][j] == 0 && a[n - 1 - i][j] == 0)) {
                        half++;
                    }
                    continue;
                }
                int k = a[i][j] + a[n - 1 - i][j] + a[i][m - 1 - j] + a[n - 1 - i][m - 1 - j];
                ans += min(k, 4 - k);
            }
        }
        if (ct == 2 && half > 0) {
            ct = 0, half--, ans++;
        }
        ans += ct + half;
        return ans;
    }
};
