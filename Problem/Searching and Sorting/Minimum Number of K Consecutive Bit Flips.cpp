//https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/description/
class Solution {
public:
    int val[100005];

    int minKBitFlips(vector<int>& a, int k) {
        int n = a.size(), sum = 0, ans = 0;
        for (int i = 0; i <= n - k; i++) {
            sum ^= val[i];
            int x = a[i] ^ sum;
            if (x == 0) {
                ans++;
                sum ^= 1;
                val[i + k] ^= 1;
            }
        }
        for (int i = n - k + 1; i < n; i++) {
            sum ^= val[i];
            int x = a[i] ^ sum;
            if (x == 0) {
                return -1;
            }
        }
        return ans;
    }
};
