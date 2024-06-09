//https://leetcode.com/contest/weekly-contest-350/problems/painting-the-walls/
class Solution {
public:
    map<int, int> dp;
    map<int, int> dp_next;
    int INF = 1e9;
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        dp[-1] = 0;
        dp[min(n, time[0])] = cost[0];
        for (int i = 1; i < n; i++) {
            for (auto it = dp.begin(); it != dp.end(); ++it) {
                int j = it->first;
                auto f0 = dp_next.find(j - 1);
                if (f0 == dp_next.end()) {
                    dp_next[j - 1] = it->second;
                } else {
                    f0->second = min(f0->second, it->second);
                }
                auto f1 = dp_next.find(min(n, j + time[i]));
                if (f1 == dp_next.end()) {
                     dp_next[min(n, j + time[i])] = it->second + cost[i];
                } else {
                    f1->second = min(f1->second, it->second + cost[i]);
                }

            }
            dp = dp_next;
            dp_next.clear();
        }
        int ans = INF;
        for (auto it = dp.begin(); it != dp.end(); ++it) {
            if (it->first >= 0) {
                ans = min(ans, it->second);
            }
        }

        return ans;
    }
};
