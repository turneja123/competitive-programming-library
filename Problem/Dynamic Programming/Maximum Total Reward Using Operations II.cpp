//https://leetcode.com/contest/weekly-contest-401/problems/maximum-total-reward-using-operations-ii/
class Solution {
public:
    bitset<100005> ans;
    bitset<100005> id;

    int maxTotalReward(vector<int>& a) {
        sort(a.begin(), a.end());
        int j = 0;
        for (int i = 0; i < a.size(); i++) {
            while (j < a[i]) {
                id.set(j++);
            }
            ans |= (ans & id) << a[i];
            ans.set(a[i]);
        }
        int mx = 0;
        for (int i = 0; i <= 2 * a[a.size() - 1]; i++) {
            if (ans[i]) {
                mx = i;
            }
        }
        return mx;
    }
};
