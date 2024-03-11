//https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        long long ans = 1e15;
        tree <pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;
        long long cur = 0;
        int n = nums.size();
        k--;
        for (int i = 1; i <= dist + 1; i++) {
            if (t.order_of_key(make_pair(nums[i], i)) < k) {
                cur += nums[i];
                t.insert(make_pair(nums[i], i));
                if (t.size() > k) {
                    cur -= (t.find_by_order(k))->first;
                }
            } else {
                t.insert(make_pair(nums[i], i));
            }
        }
        ans = min(ans, cur);
        int j = 1;
        for (int i = dist + 2; i < n; i++) {
            if (t.order_of_key(make_pair(nums[j], j)) < k) {
                t.erase(make_pair(nums[j], j));
                cur -= nums[j];
                if (t.size() >= k) {
                    cur += (t.find_by_order(k - 1))->first;
                }
            } else {
                t.erase(make_pair(nums[j], j));
            }
            if (t.order_of_key(make_pair(nums[i], j)) < k) {
                cur += nums[i];
                t.insert(make_pair(nums[i], i));
                if (t.size() > k) {
                    cur -= (t.find_by_order(k))->first;
                }
            } else {
                t.insert(make_pair(nums[i], i));
            }
            ans = min(ans, cur);
            j++;
        }
        while (n - j > k) {
            if (t.order_of_key(make_pair(nums[j], j)) < k) {
                t.erase(make_pair(nums[j], j));
                cur -= nums[j];
                if (t.size() >= k) {
                    cur += (t.find_by_order(k - 1))->first;
                }
            } else {
                t.erase(make_pair(nums[j], j));
            }
            ans = min(ans, cur);
            j++;  
        }
        return ans + nums[0];
    }
};