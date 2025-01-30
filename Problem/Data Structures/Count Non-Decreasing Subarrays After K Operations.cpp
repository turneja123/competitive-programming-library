//https://leetcode.com/contest/weekly-contest-432/problems/count-non-decreasing-subarrays-after-k-operations/
const int N = 1e5 + 5;
const int INF = 2e9;

struct Node {
    long long sum;
    int mn1;
    int mn2;
    int mnc;
    Node() {}
    Node(long long x) : sum(x), mn1(x), mn2(INF), mnc(1) {}
};

long long pref[N];
Node segtree[4 * N];

class Solution {
public:
    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = left.sum + right.sum;
        if (left.mn1 == right.mn1) {
            node.mn1 = left.mn1;
            node.mn2 = min(left.mn2, right.mn2);
            node.mnc = left.mnc + right.mnc;
        } else if (left.mn1 < right.mn1) {
            node.mn1 = left.mn1;
            node.mn2 = min(left.mn2, right.mn1);
            node.mnc = left.mnc;
        } else {
            node.mn1 = right.mn1;
            node.mn2 = min(left.mn1, right.mn2);
            node.mnc = right.mnc;
        }
        return node;
    }

    void apply_min(int node, int l, int r, long long val) {
        if (segtree[node].mn1 >= val) {
            return;
        }
        segtree[node].sum -= (long long)(segtree[node].mn1 - val) * segtree[node].mnc;
        segtree[node].mn1 = val;
        return;
    }

    void compose(int node, int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        apply_min(2 * node + 1, l, mid, segtree[node].mn1);
        apply_min(2 * node + 2, mid + 1, r, segtree[node].mn1);
        return;
    }

    long long query_sum(int l, int r, int lq, int rq, int node) {
        if (l > rq || r < lq) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return segtree[node].sum;
        }
        compose(node, l, r);
        int mid = (l + r) / 2;
        return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
    }

    void update_max(int l, int r, int lq, int rq, int val, int node) {
        if (r < lq || l > rq || segtree[node].mn1 >= val) {
            return;
        }
        if (l >= lq && r <= rq && segtree[node].mn2 > val) {
            apply_min(node, l, r, val);
            return;
        }
        int mid = (l + r) / 2;
        compose(node, l, r);
        update_max(l, mid, lq, rq, val, 2 * node + 1);
        update_max(mid + 1, r, lq, rq, val, 2 * node + 2);
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

    long long countNonDecreasingSubarrays(vector<int>& a, int k) {
        int n = a.size();
        reverse(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
        }
        build(0, n - 1, 0, a);
        long long ans = 0;
        for (int i = 0, l = 0; i < n; i++) {
            update_max(0, n - 1, 0, i, a[i], 0);
            long long orig = pref[i] - (l == 0 ? 0 : pref[l - 1]);
            while (query_sum(0, n - 1, l, i, 0) - orig > k) {
                l++;
                orig = pref[i] - (l == 0 ? 0 : pref[l - 1]);
            }
            ans += i - l + 1;
        }
        return ans;
    }
};
