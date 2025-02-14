//https://leetcode.com/contest/weekly-contest-436/problems/count-substrings-divisible-by-last-digit/
class Solution {
public:
    int freq[10][10];
    int nx[10][10];
    long long countSubstrings(string s) {
        long long ans = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int c = s[i] - '0';
            for (int j = 1; j < 10; j++) {
                for (int m = 0; m < j; m++) {
                    nx[j][(m * 10 + c) % j] += freq[j][m];
                }
            }
            for (int j = 1; j < 10; j++) {
                for (int m = 0; m < j; m++) {
                    freq[j][m] = nx[j][m];
                    nx[j][m] = 0;
                }
            }
            for (int j = 1; j < 10; j++) {
                freq[j][c % j]++;
            }
            if (c > 0) {
                ans += freq[c][0];
            }

        }
        return ans;
    }
};
