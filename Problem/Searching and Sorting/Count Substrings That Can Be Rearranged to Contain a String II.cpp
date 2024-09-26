//https://leetcode.com/contest/weekly-contest-416/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/
class Solution {
public:
    int ct[26];
    int cur[26];

    long long validSubstringCount(string a, string b) {
        for (int i = 0; i < b.size(); i++) {
            ct[b[i] - 'a']++;
        }
        int bad = 0;
        for (int j = 0; j < 26; j++) {
            if (ct[j] > 0) {
                bad++;
            }
        }
        int i = 0;
        int n = a.size();
        while (i < n && bad > 0) {
            cur[a[i] - 'a']++;
            if (cur[a[i] - 'a'] == ct[a[i] - 'a']) {
                bad--;
            }
            i++;
        }
        i--;
        int st = i;
        if (bad > 0) {
            return 0;
        }
        long long ans = 0;
        int l = 0;
        for (i; i < n; i++) {
            if (st != i) {
                cur[a[i] - 'a']++;
            }
            while (l < i) {
                cur[a[l] - 'a']--;
                if (cur[a[l] - 'a'] == ct[a[l] - 'a'] - 1) {
                    cur[a[l] - 'a']++;
                    break;
                }
                l++;
            }
            ans += l + 1;
        }
        return ans;
    }
};
