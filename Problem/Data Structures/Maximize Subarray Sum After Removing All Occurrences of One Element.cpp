//https://leetcode.com/contest/biweekly-contest-147/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/
const int N = 1e5 + 5;
const long long INF = 1e16;
struct Node {
    long long pref;
    long long suf;
    long long sum;
    long long val;
    Node() : pref(0), suf(0), sum(0), val(0) {}
    Node(long long x) : pref(x), suf(x), sum(x), val(x) {}
};
Node segtree[4 * N];
class Solution {
public:
    Node combine(Node left, Node right) {
        Node node = Node();
        node.sum = left.sum + right.sum;
        node.pref = max(left.pref, left.sum + right.pref);
        node.suf = max(right.suf, right.sum + left.suf);
        node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
        return node;
    }

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node] = Node(val);
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2);
        }
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


    long long maxSubarraySum(vector<int>& a) {
        map<int, vector<int>> mp;
        int n = a.size();
        int mx = -INF;
        for (int i = 0; i < n; i++) {
            mp[a[i]].push_back(i);
            mx = max(mx, a[i]);
        }
        if (mx < 0) {
            return mx;
        }
        build(0, n - 1, 0, a);
        long long ans = segtree[0].val;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            vector<int> v = it->second;
            if (v.size() == n) {
                break;
            }
            for (int j : v) {
                update(0, n - 1, j, 0, 0);
            }
            ans = max(ans, segtree[0].val);
            for (int j : v) {
                update(0, n - 1, j, it->first, 0);
            }
        }
        return ans;
    }
};
