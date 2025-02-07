//https://leetcode.com/contest/biweekly-contest-149/problems/reschedule-meetings-for-maximum-free-time-ii/
class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& s, vector<int>& e) {
        vector<int> gap;
        int n = s.size();
        gap.push_back(s[0]);
        for (int i = 1; i < n; i++) {
            gap.push_back(s[i] - e[i - 1]);
        }
        gap.push_back(eventTime - e[n - 1]);
        multiset<int> st;
        int ans = 0;
        for (int x : gap) {
            ans = max(ans, x);
            st.insert(x);
        }
        for (int i = 0; i < n; i++) {
            ans = max(ans, gap[i] + gap[i + 1]);
            st.erase(st.find(gap[i]));
            st.erase(st.find(gap[i + 1]));
            if (*st.rbegin() >= e[i] - s[i]) {
                ans = max(ans, gap[i] + gap[i + 1] + e[i] - s[i]);
            }
            st.insert(gap[i]);
            st.insert(gap[i + 1]);
        }
        return ans;
    }
};
