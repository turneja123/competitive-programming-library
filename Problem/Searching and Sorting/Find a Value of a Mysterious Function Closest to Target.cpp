//https://leetcode.com/contest/weekly-contest-198/problems/find-a-value-of-a-mysterious-function-closest-to-target/
class Solution {
public:
    int closestToTarget(vector<int>& a, int target) {
        map<int, int> mp;
        int ans = abs(a[0] - target), n = a.size();
        mp[a[0]] = 0;
        for (int i = 1; i < n; i++) {
            map<int, int> nx;
            nx[a[i]] = i;
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                int g = it->first & a[i];
                auto f = nx.find(g);
                if (f == nx.end()) {
                    nx[g] = it->second;
                } else {
                    nx[g] = min(nx[g], it->second);
                }
            }
            mp = nx;
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                ans = min(ans, abs(it->first - target));
            }
        }
        return ans;
    }
};
};
