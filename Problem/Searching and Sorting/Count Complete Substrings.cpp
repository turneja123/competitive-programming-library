//https://leetcode.com/contest/weekly-contest-374/problems/count-complete-substrings/
class Solution {
public:
    int pref[100005];
    int ans = 0;
    void calc(string &s, int k, int m) {
        int n = s.size();
        if (k * m > n) {
            return;
        }
        vector<int> freq(26, 0);
        int ct = 0;
        for (int i = 0; i < k * m; i++) {
            int c = s[i] - 'a';
            if (freq[c] == k) {
                ct--;
            }
            freq[c]++;
            if (freq[c] == k) {
                ct++;
            }
        }
        if (ct == m && pref[k * m - 1] == 0) {
            ans++;
        }
        for (int i = k * m; i < n; i++) {
            int c = s[i - k * m] - 'a';
            if (freq[c] == k) {
                ct--;
            }
            freq[c]--;
            if (freq[c] == k) {
                ct++;
            }
            c = s[i] - 'a';
            if (freq[c] == k) {
                ct--;
            }
            freq[c]++;
            if (freq[c] == k) {
                ct++;
            }
            if (ct == m && pref[i] - pref[i - k * m + 1] == 0) {
                ans++;
            }
        }
    }
    
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        for (int i = 1; i < n; i++) {
            int ca = word[i] - 'a', cb = word[i - 1] - 'a';
            if (abs(ca - cb) > 2) {
                pref[i]++;
            }
            pref[i] += pref[i - 1];
            
        }
        for (int i = 1; i <= 26; i++) {
            calc(word, k, i);
        }
        return ans;
        
    }
};