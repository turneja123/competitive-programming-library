//https://leetcode.com/contest/weekly-contest-387/problems/distribute-elements-into-two-arrays-ii/
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        tree <pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ta, tb;
        vector<int> a, b;
        a.push_back(nums[0]);
        b.push_back(nums[1]);
        ta.insert(make_pair(nums[0], 0));
        tb.insert(make_pair(nums[1], 1));
        int inf = 2e9;
        for (int i = 2; i < nums.size(); i++) {
            int ac = ta.size() - ta.order_of_key(make_pair(nums[i], inf));
            int bc = tb.size() - tb.order_of_key(make_pair(nums[i], inf));
            if (ac > bc) {
                a.push_back(nums[i]);
                ta.insert(make_pair(nums[i], i));
            } else if (ac < bc) {
                b.push_back(nums[i]);
                tb.insert(make_pair(nums[i], i)); 
            } else if (a.size() < b.size()) {
                a.push_back(nums[i]);
                ta.insert(make_pair(nums[i], i));
            } else if (a.size() > b.size()) {
                b.push_back(nums[i]);
                tb.insert(make_pair(nums[i], i)); 
            } else {
                a.push_back(nums[i]);
                ta.insert(make_pair(nums[i], i));
            }
        }
        vector<int> ans;
        for (int x : a) {
            ans.push_back(x);
        }
        for (int x : b) {
            ans.push_back(x);
        }
        
        return ans;
        
    }
};