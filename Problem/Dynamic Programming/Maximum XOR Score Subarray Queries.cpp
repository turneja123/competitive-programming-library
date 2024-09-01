//https://leetcode.com/contest/weekly-contest-413/problems/maximum-xor-score-subarray-queries/
int val[2005][2005];

class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& a, vector<vector<int>>& queries) {
        int n = a.size();
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(a[i]);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < v.size(); j++) {
                val[j][i + j] = v[j];
            }
            for (int j = 0; j < v.size() - 1; j++) {
                v[j] = v[j] ^ v[j + 1];
            }
            v.pop_back();
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j + i < n; j++) {
                if (i == 0) {
                    continue;
                }
                val[j][j + i] = max({val[j][j + i], val[j][j + i - 1], val[j + 1][j + i]});
            }
        }
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            ans.push_back(val[queries[i][0]][queries[i][1]]);
        }
        return ans;
    }
};
