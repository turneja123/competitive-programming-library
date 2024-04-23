//https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/description/
#pragma GCC optimize("O3")
class Solution {
public:
    int freq[100005][26];
    int p[26];
    vector<int> pos[26];
    int uniqueLetterString(string s) {
        for (int i = 0; i < s.size(); i++) {
            pos[s[i] - 'A'].push_back(i);
        }
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < 26; j++) {
                if (p[j] < pos[j].size()) {
                    ans += ((p[j] + 1 < pos[j].size()) ? pos[j][p[j] + 1] : s.size())  - pos[j][p[j]];
                }
            }
            p[s[i] - 'A']++;
        }
        return ans;
    }
};