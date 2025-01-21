//https://leetcode.com/contest/weekly-contest-433/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/
const int N = 1e6 + 5;
const int INF = 2e9;

int mode = 0;

struct Node {
    long long sum;
    int mx1;
    int mx2;
    int mxc;
    Node() : sum(0), mx1(0), mx2(0), mxc(0) {}
    Node(int x) : sum(x), mx1(x), mx2((mode == 0 ? -INF : INF)), mxc(1) {}
};

Node segtree[4 * N];

class Solution {
public:
    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = left.sum + right.sum;
        if (!mode) {
            if (left.mx1 == right.mx1) {
                node.mx1 = left.mx1;
                node.mx2 = max(left.mx2, right.mx2);
                node.mxc = left.mxc + right.mxc;
            } else if (left.mx1 > right.mx1) {
                node.mx1 = left.mx1;
                node.mx2 = max(left.mx2, right.mx1);
                node.mxc = left.mxc;
            } else {
                node.mx1 = right.mx1;
                node.mx2 = max(left.mx1, right.mx2);
                node.mxc = right.mxc;
            }
        } else {
            if (left.mx1 == right.mx1) {
                node.mx1 = left.mx1;
                node.mx2 = min(left.mx2, right.mx2);
                node.mxc = left.mxc + right.mxc;
            } else if (left.mx1 < right.mx1) {
                node.mx1 = left.mx1;
                node.mx2 = min(left.mx2, right.mx1);
                node.mxc = left.mxc;
            } else {
                node.mx1 = right.mx1;
                node.mx2 = min(left.mx1, right.mx2);
                node.mxc = right.mxc;
            }

        }
        return node;
    }

    void apply(int node, int l, int r, int val) {
        if (!mode) {
            if (segtree[node].mx1 <= val) {
                return;
            }
            segtree[node].sum -= (long long)(segtree[node].mx1 - val) * segtree[node].mxc;
            segtree[node].mx1 = val;
        } else {
            if (segtree[node].mx1 >= val) {
                return;
            }
            segtree[node].sum -= (long long)(segtree[node].mx1 - val) * segtree[node].mxc;
            segtree[node].mx1 = val;
        }
        return;
    }


    long long query_sum(int l, int r, int lq, int rq, int node) {
        if (l > rq || r < lq) {
            return 0;
        }

        if (lq <= l && rq >= r) {
            return segtree[node].sum;
        }
        int mid = (l + r) / 2;
        apply(2 * node + 1, l, mid, segtree[node].mx1);
        apply(2 * node + 2, mid + 1, r, segtree[node].mx1);
        return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
    }

    void update(int l, int r, int lq, int rq, int val, int node) {
        if (!mode) {
            if (r < lq || l > rq || segtree[node].mx1 <= val) {
                return;
            }
            if (l >= lq && r <= rq && segtree[node].mx2 < val) {
                apply(node, l, r, val);
                return;
            }
        } else {
            if (r < lq || l > rq || segtree[node].mx1 >= val) {
                return;
            }
            if (l >= lq && r <= rq && segtree[node].mx2 > val) {
                apply(node, l, r, val);
                return;
            }
        }
        int mid = (l + r) / 2;
        apply(2 * node + 1, l, mid, segtree[node].mx1);
        apply(2 * node + 2, mid + 1, r, segtree[node].mx1);
        update(l, mid, lq, rq, val, 2 * node + 1);
        update(mid + 1, r, lq, rq, val, 2 * node + 2);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }


    void build(int l, int r, int node, vector<int> &a) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = Node(a[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1, a);
        build(mid + 1, r, 2 * node + 2, a);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }


    long long minMaxSubarraySum(vector<int>& nums, int k) {
        long long ans = 0;
        mode = 0;
        int n = nums.size();
        build(0, n - 1, 0, nums);
        for (int i = 0; i < n; i++) {
            update(0, n - 1, 0, i, nums[i], 0);
            int l = max(0, i - k + 1);
            ans += query_sum(0, n - 1, l, i, 0);
        }
        mode = 1;
        build(0, n - 1, 0, nums);
        for (int i = 0; i < n; i++) {
            update(0, n - 1, 0, i, nums[i], 0);
            int l = max(0, i - k + 1);
            ans += query_sum(0, n - 1, l, i, 0);
        }
        return ans;
    }
};
