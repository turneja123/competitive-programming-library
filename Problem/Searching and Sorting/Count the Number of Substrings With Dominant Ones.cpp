//https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/description/
class Solution {
public:
    long long ans = 0;
    void calc(vector<int> &pos, int i, int j, int n) {
        if (j == pos.size()) {
            ans += n - i;
            return;
        }
        ans += pos[j] - i;
        int ct = pos[j] - i;
        for (int k = j; k < pos.size(); k++) {
            int lim = (k - j + 1) * (k - j + 1);
            if (lim >= n) {
                break;
            }
            int l = max(pos[k], pos[k] + lim - ct), r = ((k == pos.size() - 1) ? n : pos[k + 1]);
            if (l < r) {
                ans += r - l;
            }

            if (k != pos.size() - 1) {
                ct += pos[k + 1] - pos[k] - 1;
            }
        }

    }

    int numberOfSubstrings(string s) {
        vector<int> pos;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                pos.push_back(i);
            }
        }
        int j = 0;
        for (int i = 0; i < n; i++) {
            calc(pos, i, j, n);
            if (j < pos.size() && pos[j] == i) {
                j++;
            }
        }
        return ans;
    }
};
