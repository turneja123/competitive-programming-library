//https://leetcode.com/contest/weekly-contest-419/problems/find-x-sum-of-all-k-long-subarrays-ii/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree <pair<int, int>, null_type, greater<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;
map<int, int> freq;

class Solution {
public:
    long long ans = 0;
    void st_add(int n, int x, int add) {
        x = min(x, (int)t.size());
        int frek = freq[n];
        int ct = t.order_of_key(make_pair(frek, n));
        int ch = 0;
        if (ct < x) {
            ans -= (long long)frek * n;
            t.erase(make_pair(frek, n));
            auto it = t.find_by_order(x - 1);
            ans += (long long)it->first * it->second;
        } else {
            t.erase(make_pair(frek, n));
        }
        frek += add;
        freq[n] = frek;
        ct = t.order_of_key(make_pair(frek, n));
        if (ct < x) {
            auto it = t.find_by_order(x - 1);
            ans -= (long long)it->first * it->second;
            ans += (long long)frek * n;
            t.insert(make_pair(frek, n));
        } else {
            t.insert(make_pair(frek, n));
        }
        return;
    }

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            t.insert(make_pair(0, nums[i]));
        }
        vector<long long> v;
        for (int i = 0; i < k; i++) {
            st_add(nums[i], x, 1);
        }
        v.push_back(ans);
        for (int i = k; i < n; i++) {
            st_add(nums[i - k], x, -1);
            st_add(nums[i], x, 1);
            v.push_back(ans);
        }
        t.clear();
        freq.clear();
        return v;
    }
};
