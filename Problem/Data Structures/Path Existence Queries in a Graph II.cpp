//https://leetcode.com/contest/weekly-contest-447/problems/path-existence-queries-in-a-graph-ii/
const int N = 1e5 + 5;
const int K = 20;
int up[K][N];
int pos[N];
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back(make_pair(nums[i], i));
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            pos[a[i].second] = i;
            int j = upper_bound(a.begin(), a.end(), make_pair(a[i].first + maxDiff, N)) - a.begin() - 1;
            up[0][i] = j;
        }
        for (int k = 1; k < K; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }
        int q = queries.size();
        vector<int> ans(q, 0);
        for (int i = 0; i < q; i++) {
            int l = queries[i][0], r = queries[i][1];
            l = pos[l], r = pos[r];
            if (l > r) {
                swap(l, r);
            }
            if (l == r) {
                ans[i] = 0;
                continue;
            }
            for (int k = K - 1; k >= 0; k--) {
                if (up[k][l] < r) {
                    ans[i] += 1 << k;
                    l = up[k][l];
                }
            }
            if (l < r) {
                if (up[0][l] >= r) {
                    ans[i]++;
                } else {
                    ans[i] = -1;

                }
            }
        }
        return ans;
    }
};
