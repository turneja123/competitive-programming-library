//https://leetcode.com/contest/weekly-contest-399/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/
class Solution {
public:
    long long segtree[50005*4][2][2];
    long long a[50005];
    long long M = 1e9 + 7;

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node][1][1] = val;
            return;
        }

        int mid = (l + r) / 2, ln = 2 * node + 1, rn = 2 * node + 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2);
        }
        segtree[node][0][0] = max({segtree[ln][0][0] + segtree[rn][0][0], 
                                   segtree[ln][0][1] + segtree[rn][0][0], segtree[ln][0][0] + segtree[rn][1][0]});
        segtree[node][1][0] = max({segtree[ln][1][0] + segtree[rn][0][0], 
                                   segtree[ln][1][1] + segtree[rn][0][0], segtree[ln][1][0] + segtree[rn][1][0]});
        segtree[node][0][1] = max({segtree[ln][0][0] + segtree[rn][0][1], 
                                   segtree[ln][0][1] + segtree[rn][0][1], segtree[ln][0][0] + segtree[rn][1][1]});
        segtree[node][1][1] = max({segtree[ln][1][0] + segtree[rn][0][1], 
                                   segtree[ln][1][1] + segtree[rn][0][1], segtree[ln][1][0] + segtree[rn][1][1]});
    }


    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node][0][0] = 0;
            segtree[node][0][1] = 0;
            segtree[node][1][0] = 0;
            segtree[node][1][1] = a[l];
            return;
        }

        int mid = (l + r) / 2, ln = 2 * node + 1, rn = 2 * node + 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node][0][0] = max({segtree[ln][0][0] + segtree[rn][0][0], 
                                   segtree[ln][0][1] + segtree[rn][0][0], segtree[ln][0][0] + segtree[rn][1][0]});
        segtree[node][1][0] = max({segtree[ln][1][0] + segtree[rn][0][0], 
                                   segtree[ln][1][1] + segtree[rn][0][0], segtree[ln][1][0] + segtree[rn][1][0]});
        segtree[node][0][1] = max({segtree[ln][0][0] + segtree[rn][0][1], 
                                   segtree[ln][0][1] + segtree[rn][0][1], segtree[ln][0][0] + segtree[rn][1][1]});
        segtree[node][1][1] = max({segtree[ln][1][0] + segtree[rn][0][1], 
                                   segtree[ln][1][1] + segtree[rn][0][1], segtree[ln][1][0] + segtree[rn][1][1]});
    }
    
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            a[i] = nums[i];
        }
        build(0, n - 1, 0);
        long long ans = 0;
        for (int i = 0; i < queries.size(); i++) {
            update(0, n - 1, queries[i][0], queries[i][1], 0);
            ans = (ans + max({segtree[0][0][0], segtree[0][0][1], segtree[0][1][0], segtree[0][1][1]})) % M;
        }
        return ans;
        
        
    }
};