//https://leetcode.com/contest/weekly-contest-372/problems/maximum-xor-product/
const long long M = 1e9 + 7;
class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        int f = 0;
        if (a > b) {
            swap(a, b);
        }
        for (int i = 60; i >= n; i--) {
            long long ca = a & (1ll << i), cb = b & (1ll << i);
            if (ca != cb) {
                f = 2;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            long long ca = a & (1ll << i), cb = b & (1ll << i);
            if (ca == cb) {
                a |= 1ll << i;
                b |= 1ll << i;
                continue;
            }
            if (f == 2) {
                a |= 1ll << i;
                b &= ~(1ll << i);
                continue;
            }
            if (!f) {
                a |= 1ll << i;
                b &= ~(1ll << i);
                f = 1;
            } else {
                b |= 1ll << i;
                a &= ~(1ll << i);
            }
        }
        long long ans = (a % M) * (b % M) % M;
        return ans;
    }
};
