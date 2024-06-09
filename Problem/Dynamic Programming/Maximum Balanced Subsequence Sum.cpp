//https://leetcode.com/contest/weekly-contest-370/problems/maximum-balanced-subsequence-sum/
class Solution {
public:
    long long segtree[400005];
    long long INF = 1e18;

    long long rmq(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return -INF;
        }

        int mid = (l + r) / 2;
        return max(rmq(l, mid, lq, rq, 2 * node + 1),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void update(int l, int r, int ind, long long val, int node) {
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
        segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    }
    void build(int l, int r, int node) {
        if (l == r) {
            segtree[node] = -INF;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = -INF;
    }

    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();
        set<int> st;
        map<int, int> pos;
        for (int i = 0; i < n; i++) {
            st.insert(nums[i] + n - 1 - i);
        }
        int j = 0;
        for (int x : st) {
            pos[x] = j++;
        }
        int m = st.size();
        build(0, m - 1, 0);
        long long ans = -INF;
        for (int i = 0; i < n; i++) {
            int ind = pos[nums[i] + n - 1 - i];
            long long mx = rmq(0, m - 1, 0, ind, 0);
            if (mx > 0 && nums[i] > 0) {
                mx += nums[i];
            }
            mx = max(mx, (long long)nums[i]);
            update(0, m - 1, ind, mx, 0);
            ans = max(ans, mx);
        }
        return ans;
    }
};
