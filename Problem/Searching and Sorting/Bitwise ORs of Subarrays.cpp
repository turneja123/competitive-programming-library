//https://leetcode.com/problems/bitwise-ors-of-subarrays/description/
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& a) {
        set<int> ans;
        ans.insert(a[0]);
        set<int> last = ans;
        for (int i = 1; i < a.size(); i++) {
            set<int> st;
            st.insert(a[i]); ans.insert(a[i]);
            for (int x : last) {
                st.insert(x | a[i]);
                ans.insert(x | a[i]);
            }
            last = st;
        }
        return ans.size();
    }
};
