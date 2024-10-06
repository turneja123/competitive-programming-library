//https://leetcode.com/contest/weekly-contest-417/problems/find-the-k-th-character-in-string-game-ii/
class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        vector<int> x;
        while (k > 1) {
            long long ind = (long long)log2(k - 1);
            long long b = (long long)1 << ind;
            k -= b;
            x.push_back(ind);
        }
        reverse(x.begin(), x.end());
        char c = 'a';
        for (int i = 0; i < x.size(); i++) {
            if (operations[x[i]] == 1) {
                if (c == 'z') {
                    c = 'a';
                } else {
                    c++;
                }
            }
        }
        return c;
    }
};
