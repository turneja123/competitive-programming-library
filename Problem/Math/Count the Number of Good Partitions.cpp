//https://leetcode.com/problems/count-the-number-of-good-partitions/description/
const int N = 1e5 + 5;
const long long M = 1e9 + 7;

class Solution {
public:
    int pref[N];

    int numberOfGoodPartitions(vector<int>& nums) {
        map<int, int> right;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            right[nums[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            pref[i] = i == 0 ? right[nums[i]] : max(pref[i - 1], right[nums[i]]);
        }
        int i = 0, j = 0;
        while (i < n) {
            while (i != pref[i]) {
                i = pref[i];
            }
            i++, j++;
        }
        long long ans = 1;
        for (int i = 0; i < j - 1; i++) {
            ans = ans * 2 % M;
        }
        return ans;
    }
};
