//https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/description/
const int INF = 1e9;
class Solution {
public:
    int minOperations(string s, int k) {
        int n = 0, m = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                n++;
            } else {
                m++;
            }
        }
        if (k == n + m) {
            if (n == 0) {
                return 0;
            } else if (m == 0) {
                return 1;
            } else {
                return -1;
            }
        }
        int ans = INF;
        if (n % 2 == 0) {
            int x = max((n + k - 1) / k, (n + n + m - k - 1) / (n + m - k));
            if (x % 2 == 1) {
                x++;
            }
            ans = min(ans, x);
        }
        if (n % 2 == k % 2) {
            int x = max((n + k - 1) / k, (m + n + m - k - 1) / (n + m - k));
            if (x % 2 == 0) {
                x++;
            }
            ans = min(ans, x);
        }
        if (ans > n + m) {
            return -1;
        }
        return ans;
    }
};
