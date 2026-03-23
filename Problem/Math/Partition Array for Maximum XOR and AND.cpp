//https://leetcode.com/problems/partition-array-for-maximum-xor-and-and/description/
class Solution {
public:

    void insert_vector(int a, vector<int> &basis) {
        for (int i = 29; i >= 0; i--) {
            long long c = a & (1ll << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                return;
            }
            a ^= basis[i];
        }
    }


    long long maximizeXorAndXor(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        for (int j_and = 0; j_and < 1 << n; j_and++) {

            int v_and = (1 << 30) - 1, v_xor = 0;
            if (j_and == 0) {
                v_and = 0;
            }
            vector<int> basis(30, 0);

            for (int i = 0; i < n; i++) {
                int c = j_and & (1 << i);
                if (c) {
                    v_and &= nums[i];
                } else {
                    v_xor ^= nums[i];
                }
            }
            for (int i = 0; i < n; i++) {
                int c = j_and & (1 << i);
                if (c) {
                    continue;
                }

                int comple = ((1 << 30) - 1) ^ v_xor;
                insert_vector(nums[i] & comple, basis);
            }
            int a = 0; long long v_other = 0;
            for (int i = 29; i >= 0; i--) {
                int c = v_xor & (1 << i);
                if (c) {
                    continue;
                }
                int need = ((1 << i) ^ a) & (1 << i);
                if (!need) {
                    a ^= 1 << i;
                    v_other += (long long)2 * (1 << i);
                    continue;
                }
                if (!basis[i]) {
                    continue;
                }
                a ^= 1 << i;
                v_other += (long long)2 * (1 << i);
                a ^= basis[i];
            }
            ans = max(ans, v_other + v_xor + v_and);
        }
        return ans;
    }
};
