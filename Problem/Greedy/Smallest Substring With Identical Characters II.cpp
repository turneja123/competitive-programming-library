//https://leetcode.com/contest/weekly-contest-429/problems/smallest-substring-with-identical-characters-ii/
class Solution {
public:
    int minLength(string s, int numOps) {
        int cur = 1; char last = s[0];
        vector<int> a;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != last) {
                a.push_back(cur);
                cur = 0;
                last = s[i];
            }
            cur++;
        }
        a.push_back(cur);
        vector<int> cost(2, 0);
        vector<char> c{'0', '1'};
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != c[(0 + i) % 2]) {
                cost[0]++;
            }
            if (s[i] != c[(1 + i) % 2]) {
                cost[1]++;
            }
        }
        if (min(cost[0], cost[1]) <= numOps) {
            return 1;
        }
        int l = 2, r = s.size(), ans = r;
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur = 0;
            for (int i = 0; i < a.size(); i++) {
                cur += a[i] / (mid + 1);
            }
            if (cur <= numOps) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
