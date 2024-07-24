//https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/description/
class Solution {
public:
    long long add = 0;

    void solve(vector<int> &a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            a[i] = abs(a[i]);
        }
        add = a[0];
        for (int i = 1; i < a.size(); i ++) {
            if (a[i]>a[i-1]) {
                add += a[i]-a[i-1];
            }
        }
    }

    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = nums[i] - target[i];
        }
        vector<vector<int>> sub;
        vector<int> v;
        v.push_back(a[0]);
        for (int i = 1; i < n; i++) {
            if ((a[i - 1] < 0 && a[i] > 0) || (a[i - 1] > 0 && a[i] < 0)) {
                sub.push_back(v);
                v.clear();
            }
            v.push_back(a[i]);
        }
        sub.push_back(v);
        long long ans = 0;
        for (int i = 0; i < sub.size(); i++) {
            solve(sub[i]);
            ans += add;
            add = 0;
        }
        return ans;
    }
};
