//https://leetcode.com/contest/weekly-contest-307/problems/find-the-k-sum-of-an-array/
class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        multiset<long long> st;
        int n = nums.size();
        vector<int> a(n);
        long long tot = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                tot += nums[i];
            }
            a[i] = abs(nums[i]);
        }
        sort(a.begin(), a.end());
        st.insert(0);
        for (int i = 0; i < n; i++) {
            multiset<long long> add;
            for (long long x : st) {
                if (st.size() == k && *st.rbegin() <= x + a[i]) {
                    break;
                }
                add.insert(x + a[i]);
            }
            for (long long x : add) {
                st.insert(x);
            }
            while (st.size() > k) {
                st.erase(--st.end());
            }
        }
        return tot - *st.rbegin();
    }
};
