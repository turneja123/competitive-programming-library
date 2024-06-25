//https://leetcode.com/contest/weekly-contest-402/problems/peaks-in-array/
class Solution {
public:
    int vals[100005];
    int segtree[400005];

    int query(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return 0;
        }

        int mid = (l + r) / 2;
        return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
    }

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2);
        }
        segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
    }

    void upd(int n, int i, vector<int> &a) {
        if (i <= 0 || i >= n - 1) {
            return;
        }
        int x = 0;
        if (a[i] > a[i - 1] && a[i] > a[i + 1]) {
            x = 1;
        }
        if (vals[i] != x) {
            vals[i] = x;
            update(0, n - 1, i, x, 0);
        }
    }

    vector<int> countOfPeaks(vector<int>& a, vector<vector<int>>& queries) {

        int n = a.size();
        for (int i = 0; i < n; i++) {
            upd(n, i, a);
        }
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            if (queries[i][0] == 2) {
                a[queries[i][1]] = queries[i][2];
                upd(n, queries[i][1] - 1, a);
                upd(n, queries[i][1], a);
                upd(n, queries[i][1] + 1, a);
            } else {
                int l = queries[i][1] + 1, r = queries[i][2] - 1;
                if (l > r) {
                    ans.push_back(0);
                } else {
                    ans.push_back(query(0, n - 1, l, r, 0));
                }
            }
        }
        return ans;
    }
};
