//https://leetcode.com/problems/maximum-bitwise-and-after-increment-operations/
using ll = long long;
class Solution {
public:
    ll calc(ll a, ll b) {
        if ((a & b) == b) {
            return 0;
        }
        int p = 63 - __builtin_clzll(b & ~a);
        ll l = ~((1ll << (p + 1)) - 1), r = (1ll << p) - 1;
        ll ans = (a & l) | (1ll << p) | (b & r);
        return ans - a;
    }

    int maximumAND(vector<int>& nums, int c, int m) {
        int ans = 0, n = nums.size();
        for (int k = 30; k >= 0; k--) {
            int cur = ans | (1 << k);
            vector<ll> dist;
            for (int i = 0; i < n; i++) {
                dist.push_back(calc(nums[i], cur));
            }
            sort(dist.begin(), dist.end());
            ll cost = 0;
            for (int i = 0; i < m; i++) {
                cost += dist[i];
            }
            if (cost <= c) {
                ans |= 1 << k;
            }
        }
        return ans;
    }
};
