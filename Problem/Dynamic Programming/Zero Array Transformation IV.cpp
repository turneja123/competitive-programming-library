//https://leetcode.com/contest/weekly-contest-441/problems/zero-array-transformation-iv/
const int N = 1005;
class Solution {
public:
    bitset<N> a[10];
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int ct = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            a[i].set(nums[i]);
            ct += a[i][0];
        }
        if (ct == n) {
            return 0;
        }
        int j = 0;
        for (int k = 0; k < queries.size(); k++) {
            int l = queries[k][0], r = queries[k][1], x = queries[k][2];
            j++;
            for (int i = l; i <= r; i++) {
                a[i] |= a[i] >> x;
            }
            int ct = 0;
            for (int i = 0; i < n; i++) {
                ct += a[i][0];
            }
            if (ct == n) {
                return j;
            }
        }
        return -1;
    }
};
