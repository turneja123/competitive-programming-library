//https://leetcode.com/contest/biweekly-contest-149/problems/reschedule-meetings-for-maximum-free-time-i/
class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& s, vector<int>& e) {
        int ans = 0;
        vector<int> gap;
        int n = s.size();
        if (s[0] != 0) {
            gap.push_back(s[0]);
        }
        for (int i = 1; i < n; i++) {
            gap.push_back(s[i] - e[i - 1]);
        }
        if (e[n - 1] != eventTime) {
            gap.push_back(eventTime - e[n - 1]);
        }
        k++;
        k = min(k, (int)gap.size());
        int cur = 0;
        for (int i = 0; i < k; i++) {
            cur += gap[i];
        }
        ans = max(ans, cur);
        for (int i = k; i < gap.size(); i++) {
            cur -= gap[i - k];
            cur += gap[i];
            ans = max(ans, cur);
        }
        return ans;
    }
};
