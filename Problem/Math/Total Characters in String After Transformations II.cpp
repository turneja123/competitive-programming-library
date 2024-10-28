//https://leetcode.com/contest/weekly-contest-421/problems/total-characters-in-string-after-transformations-ii/
const long long M = 1e9 + 7;
class Solution {
public:
    vector<vector<long long>> mul(vector<vector<long long>> base, vector<vector<long long>> mat) {
        int n = base.size(), m = mat[0].size(), k = mat.size();
        vector<vector<long long>> ret;
        ret.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int p = 0; p < k; p++) {
                    ret[i][j] += (base[i][p] * mat[p][j]) % M;
                    ret[i][j] %= M;
                }
            }
        }
        return ret;
    }

    vector<vector<long long>> expo(vector<vector<long long>> base, int n, long long k) {
        vector<vector<long long>> ans;
        ans.assign(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = (i == j);
            }
        }
        while (k) {
            if (k % 2 == 1) {
                ans = mul(ans, base);
            }
            base = mul(base, base);
            k /= 2;
        }
        return ans;
    }

    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector<vector<long long>> a;
        a.assign(26, vector<long long>(26, 0));
        for (int i = 0; i < 26; i++) {
            for (int j = i + 1; j <= i + nums[i]; j++) {
                a[j % 26][i] = 1;
            }
        }
        vector<vector<long long>> mat;
        mat.assign(26, vector<long long>(1, 0));
        for (int i = 0; i < s.size(); i++) {
            mat[s[i] - 'a'][0]++;
        }
        a = expo(a, 26, t);
        mat = mul(a, mat);
        long long ans = 0;
        for (int i = 0; i < 26; i++) {
            ans += mat[i][0];
        }
        return ans % M;

    }
};
