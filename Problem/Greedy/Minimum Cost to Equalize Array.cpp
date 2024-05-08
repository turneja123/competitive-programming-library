//https://leetcode.com/problems/minimum-cost-to-equalize-array/description/
class Solution {
public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        long long M = 1e9 + 7;
        long long mx = 0, sum = 0, n = nums.size();
        __int128 ans = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, (long long)nums[i]);
            sum += nums[i];
        }
        if (nums.size() == 1) {
            return 0;
        }
        if (nums.size() == 2) {
            return cost1 * (2 * mx - sum) % M;
        }
        if (2 * cost1 <= cost2) {
            ans = (((n * mx - sum) % M) * cost1) % M;
            return ans;
        }
        sort(nums.begin(), nums.end());
        __int128 diff = 0;
        for (int i = 1; i < n; i++) {
            diff += mx - nums[i];
        }
        if (mx - nums[0] > diff) {
            __int128 an = diff * cost2;
            nums[0] += diff;
            __int128 temp = an;
            an += (__int128)cost1 * (mx - nums[0]);
            while (nums[0] < mx) {
                mx++;
                if (nums[0] + n - 1 <= mx) {
                    temp += (__int128)cost2 * (n - 1);
                    nums[0] += n - 1;
                    an = min(an, temp + (__int128)cost1 * (mx - nums[0]));
                } else {
                    temp += (__int128)cost2 * (mx - nums[0]);
                    __int128 k = n - 1 - (mx - nums[0]);
                    temp += (__int128)cost2 * (k / 2);
                    if (k % 2 == 1) {
                        an = min(an, temp + cost1);
                        __int128 edge = 1e30; sum = n * mx - 1;
                        for (long long j = mx; j < 3e6; j++) {
                            if ((j * n - sum) % 2 == 0) {
                                edge = min(edge, (((__int128)j * n - sum) / 2) * (__int128)cost2);
                            }
                        }
                        an = min(an, temp + edge);
                    } else {
                        an = min(an, temp);
                    }
                    nums[0] = mx;
                }
            }
            an %= M;
            return an;
        }
        
        __int128 edge = 1e30;
        for (long long j = mx; j < mx + 100; j++) {
            if ((j * n - sum) % 2 == 0) {
                edge = min(edge, (((__int128)j * n - sum) / 2) * (__int128)cost2);
            }
        }
        ans += (((__int128)n * mx - sum) / 2) * cost2;
        if ((n * mx - sum) % 2 == 1) {
            ans += cost1;
        }
        ans = min(ans, edge);
        ans %= M;
        return ans;
    }
};