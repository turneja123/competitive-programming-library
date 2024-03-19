//https://leetcode.com/contest/biweekly-contest-126/problems/replace-question-marks-in-string-to-minimize-its-value/
class Solution {
public:
    string minimizeStringValue(string s) {
        string ans = s;
        int n = ans.size();
        vector<int> freq(26, 0);
        int mn = n + 1;
        for (int i = 0; i < n; i++) {
            if (s[i] != '?') {
                freq[s[i] - 'a']++;
            }
        }
        vector<int> newfreq = freq;
        for (int i = 0; i < n; i++) {
            if (ans[i] == '?') {
                int mn = n + 1;
                char best;
                for (int j = 0; j < 26; j++) {
                    if (newfreq[j] < mn) {
                        mn = newfreq[j];
                        best = 'a' + j;
                    }
                }
                newfreq[best - 'a']++;
            }
        }
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (ans[i] == '?') {
                while (j < 26 && freq[j] == newfreq[j]) {
                    j++;
                }
                char c = j + 'a';
                ans[i] = c;
                freq[j]++;
            }
        }
        return ans;
        
    }
};