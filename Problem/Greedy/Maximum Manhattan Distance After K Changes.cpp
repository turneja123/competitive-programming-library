//https://leetcode.com/contest/weekly-contest-435/problems/maximum-manhattan-distance-after-k-changes/
class Solution {
public:
    int maxDistance(string s, int kk) {
        int n = s.size();
        array<int, 2> aa{}, bb{};
        int best = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == 'N') {
                aa[0]++;
            } else if (s[i] == 'S') {
                aa[1]++;
            } else if (s[i] == 'W') {
                bb[0]++;
            } else {
                bb[1]++;
            }
            int k = kk;
            array<int, 2> a = aa, b = bb;
            if (a[1] > a[0]) {
                swap(a[1], a[0]);
            }
            int ans = a[0] - a[1];
            ans += min(k, a[1]) * 2;
            k -= min(k, a[1]);

            if (b[1] > b[0]) {
                swap(b[1], b[0]);
            }
            ans += b[0] - b[1];
            ans += min(k, b[1]) * 2;
            k -= min(k, b[1]);
            best = max(best, ans);
        }

        return best;
    }
};
