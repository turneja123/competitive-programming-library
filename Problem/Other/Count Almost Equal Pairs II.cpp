//https://leetcode.com/contest/weekly-contest-412/problems/count-almost-equal-pairs-ii/
bool seen[10000000];
int ct[10000000];
vector<int> clr;
class Solution {
public:
    int get(string &s) {
        int n = 0;
        for (int i = 0; i < s.size(); i++) {
            n += s[i] - '0';
            if (i != s.size() - 1) {
                n *= 10;
            }
        }
        return n;
    }

    int countPairs(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            ans += ct[nums[i]];
            clr.push_back(nums[i]);
            seen[nums[i]] = true;
            ct[nums[i]]++;
            string s;
            int k = nums[i];
            while (k > 0) {
                s += '0' + k % 10;
                k /= 10;
            }
            reverse(s.begin(), s.end());
            int m = s.size();
            for (int x1 = 0; x1 < m; x1++) {
                for (int x2 = x1 + 1; x2 < m; x2++) {
                    swap(s[x1], s[x2]);
                    int x = get(s);
                    if (!seen[x]) {
                        seen[x] = true;
                        clr.push_back(x);
                        ans += ct[x];
                    }

                    for (int x3 = 0; x3 < m; x3++) {
                        for (int x4 = x3 + 1; x4 < m; x4++) {
                            swap(s[x3], s[x4]);
                            int x = get(s);
                            if (!seen[x]) {
                                seen[x] = true;
                                clr.push_back(x);
                                ans += ct[x];
                            }
                            swap(s[x3], s[x4]);
                        }
                    }
                    swap(s[x1], s[x2]);
                }
            }
            for (int x : clr) {
                seen[x] = 0;
            }
            clr.clear();
        }
        for (int i = 0; i < n; i++) {
            ct[nums[i]] = 0;
        }


        return ans;
    }
};
