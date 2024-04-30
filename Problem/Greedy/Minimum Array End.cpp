//https://leetcode.com/problems/minimum-array-end/description/
class Solution {
public:
    long long minEnd(int n, int x) {
        long long m = n - 1, j = 0, ans = x;
        for (long long i = 0; i < 63; i++) {
            long long c = (long long)x & ((long long)1 << i); 
            if (c != 0) {
                continue;
            }
            c = m & ((long long)1 << j);
            if (c != 0) {
                ans += (long long)1 << i;
            }
            j++;
        }
        return ans;
        
    }
};