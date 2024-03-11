//https://leetcode.com/problems/maximum-palindromes-after-operations
class Solution {
public:
    int maxPalindromesAfterOperations(vector<string>& words) {
        vector<int> lens;
        vector<int> freq(26, 0);
        for (int i = 0; i < words.size(); i++) {
            lens.push_back(words[i].size());
            for (int j = 0; j < words[i].size(); j++) {
                int c = words[i][j] - 'a';
                freq[c]++;
            }
        }
        sort(lens.begin(), lens.end());
        int j = 0, ans = 0;
        for (int i = 0; i < lens.size(); i++) {
            for (int k = 0; k < lens[i] / 2; k++) {
                while (j < 26 && freq[j] < 2) {
                    j++;
                }
                if (j == 26) {
                    return ans;
                }
                freq[j] -= 2;
            }
            if (lens[i] % 2 == 1) {
                bool flag = false;
                for (int k = 0; k < 26 && !flag; k++) {
                    if (freq[k] % 2 == 1) {
                        freq[k]--;
                        flag = true;
                    }
                }
                if (!flag) {
                    while (j < 26 && freq[j] < 1) {
                        j++;
                    }
                    if (j == 26) { 
                        return ans;
                    }
                    freq[j]--;
                }
            }
            ans++;
        }
        return ans;
        
    }
};