//https://leetcode.com/contest/biweekly-contest-140/problems/find-the-lexicographically-smallest-valid-sequence/
const int N = 3e5 + 5;
int suf[N];

class Solution {
public:
    vector<int> validSequence(string a, string b) {
        vector<int> ans;
        int n = a.size(), m = b.size(); int j = m - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (j >= 0 && a[i] == b[j]) {
                j--;
            }
            suf[i] = j;
        }
        int can = n; j = 0;
        for (int i = 0; i < n; i++) {
            int x = ((i == n - 1) ? m - 1: suf[i + 1]);
            if (j >= x) {
                can = i;
                break;
            }
            if (j < m && a[i] == b[j]) {
                j++;
            }
        }
        if (can == n) {
            return ans;
        }
        j = 0; int used = 1;
        for (int i = 0; i < n; i++) {
            if (j < m && a[i] == b[j]) {
                ans.push_back(i);
                j++;
            } else if (j < m && can <= i && used) {
                ans.push_back(i);
                j++;
                used = 0;
            }
        }
        return ans;
    }
};
