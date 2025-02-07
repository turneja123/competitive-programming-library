//https://leetcode.com/contest/biweekly-contest-93/problems/minimum-total-cost-to-make-arrays-unequal/
class Solution {
public:
    long long minimumTotalCost(vector<int>& a, vector<int>& b) {
        int n = a.size();
        vector<int> freqa(n + 1, 0), freqb(n + 1, 0);
        int bad = 0; long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == b[i]) {
                bad++;
                freqa[a[i]]++;
                freqb[a[i]]++;
                ans += i;
            }
        }
        if (bad == 0) {
            return 0;
        }
        int fix = -1;
        for (int i = 1; i <= n; i++) {
            if (freqa[i] > bad - freqb[i]) {
                fix = i;
            }
        }
        if (fix == -1) {
            return ans;
        }
        for (int i = 0; i < n && freqa[fix] > bad - freqb[fix]; i++) {
            if (a[i] != fix && b[i] != fix && a[i] != b[i]) {
                bad++;
                ans += i;
            }
        }
        if (freqa[fix] > bad - freqb[fix]) {
            return -1;
        }
        return ans;
    }
};
