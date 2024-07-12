//https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/
class Solution {
public:
    set<int> st[20];

    int minimumDifference(vector<int>& a) {
        int n = a.size(), sum = 0;
        for (int x : a) {
            sum += x;
        }
        int na = n / 2 + n % 2, nb = n - na;
        for (int j = 0; j < (1 << na); j++) {
            int cur = 0;
            for (int i = 0; i < na; i++) {
                int c = j & (1 << i);
                if (c) {
                    cur += a[i];
                }
            }
            st[__builtin_popcount(j)].insert(cur);
        }
        int ans = 1e9;
        for (int j = 0; j < (1 << nb); j++) {
            int cur = 0;
            for (int i = 0; i < nb; i++) {
                int c = j & (1 << i);
                if (c) {
                    cur += a[i + na];
                }
            }
            int x = sum / 2 - cur, ind = n / 2 - __builtin_popcount(j);
            auto it = st[ind].lower_bound(x);
            if (it != st[ind].end()) {
                ans = min(ans, abs(sum - 2 * (cur + *it)));
            }
            if (it != st[ind].begin()) {
                --it;
                ans = min(ans, abs(sum - 2 * (cur + *it)));
            }
        }
        return ans;

    }
};
