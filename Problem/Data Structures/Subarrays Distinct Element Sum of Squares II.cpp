//https://leetcode.com/contest/biweekly-contest-116/problems/subarrays-distinct-element-sum-of-squares-ii/
class Solution {
public:
    const long long M = 1e9 + 7;

    vector<int> pos[100005];
    int p[100005];
    int freq[100005];
    long long a[100005];
    long long segtree[400005];
    long long segtree_sq[400005];

    long long lazy[400005];

    void compose(int parent, int child) {
        lazy[child] += lazy[parent];
    }

    void apply(int node, int l, int r) {
        segtree_sq[node] += segtree[node] * lazy[node] * 2  + (r - l + 1) * lazy[node] * lazy[node];
        segtree[node] += (r - l + 1) * lazy[node];
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        lazy[node] = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int add) {
        if (l > rq || lq > r || lq > rq) {
            return;
        }
        if (l >= lq && r <= rq) {
            lazy[node] += add;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, lq, rq, add);
        incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
        segtree_sq[node] = segtree_sq[node * 2 + 1] + segtree_sq[node * 2 + 2];
    }

    long long getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree_sq[node];
        }
        int mid = (l + r) / 2;
        return getSum(l, mid, lq, rq, 2 * node + 1) +
               getSum(mid + 1, r, lq, rq, 2 * node + 2);
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        lazy[node] = 0;
        if (l == r) {
            segtree[node] = a[l];
            segtree_sq[node] = a[l] * a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1);
        build(mid + 1, r, node * 2 + 2);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
        segtree_sq[node] = segtree_sq[node * 2 + 1] + segtree_sq[node * 2 + 2];
    }
    int sumCounts(vector<int>& nums) {
        int ct = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
            freq[nums[i]]++;
            if (freq[nums[i]] == 1) {
                ct++;
            }
            a[i] = ct;
        }
        build(0, n - 1, 0);
        long long ans = getSum(0, n - 1, 0, n - 1, 0);
        for (int i = 0; i < n - 1; i++) {
            int r = ((p[nums[i]] == pos[nums[i]].size() - 1) ? n - 1 : pos[nums[i]][p[nums[i]] + 1] - 1);
            incUpdate(0, 0, n - 1, i + 1, r, -1);
            ans += getSum(0, n - 1, i + 1, n - 1, 0);
            p[nums[i]]++;
        }
        int m = ans % M;
        return m;

    }
};
