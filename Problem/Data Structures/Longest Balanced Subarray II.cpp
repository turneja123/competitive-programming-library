//https://leetcode.com/problems/longest-balanced-subarray-ii/description/
const int N = 1e5 + 5;

struct Node {
    int lazy;
    int mx;
    int mn;

    Node() {
        lazy = 0;
    }
    Node(int x) {
        lazy = 0, mn = x, mx = x;
    }

};

int a[N];
int pref[N];
int last[N];
Node segtree[4 * N];

class Solution {
public:
    void apply(int l, int r, int node) {
        segtree[node].mn += segtree[node].lazy;
        segtree[node].mx += segtree[node].lazy;
        if (l != r) {
            segtree[2 * node + 1].lazy += segtree[node].lazy;
            segtree[2 * node + 2].lazy += segtree[node].lazy;
        }
        segtree[node].lazy = 0;
    }

    Node combine(Node &left, Node &right) {
        Node node;
        node.mn = min(left.mn, right.mn);
        node.mx = max(left.mx, right.mx);
        return node;
    }

    int j = -1;

    int existence(int node, int val) {
        return segtree[node].mn <= val && segtree[node].mx >= val;
    }

    void trav(int l, int r, int node, int val) {
        if (l == r) {
            j = l;
            return;
        }
        int mid = (l + r) / 2;
        apply(l, mid, 2 * node + 1);
        apply(mid + 1, r, 2 * node + 2);

        if (existence(2 * node + 1, val)) {
            trav(l, mid, 2 * node + 1, val);
        } else {
            trav(mid + 1, r, 2 * node + 2, val);
        }
    }

    void query(int l, int r, int lq, int rq, int node, int val) {
        if (l > rq || r < lq || j != -1) {
            return;
        }
        apply(l, r, node);
        if (l >= lq && r <= rq) {
            if (existence(node, val)) {
                trav(l, r, node, val);
            }
            return;
        }
        int mid = (l + r) / 2;
        query(l, mid, lq, rq, 2 * node + 1, val);
        query(mid + 1, r, lq, rq, 2 * node + 2, val);

    }

    void upd(int l, int r, int lq, int rq, int node, int val) {
        if (l > rq || r < lq) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazy += val;
            return;
        }
        apply(l, r, node);
        int mid = (l + r) / 2;
        upd(l, mid, lq, rq, 2 * node + 1, val);
        upd(mid + 1, r, lq, rq, 2 * node + 2, val);
        apply(l, mid, 2 * node + 1);
        apply(mid + 1, r, 2 * node + 2);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void build(int l, int r, int node) {
        if (l == r) {
            segtree[node] = Node(pref[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            last[nums[i]] = 0;
        }
        for (int i = 1; i <= n; i++) {
            a[i] = nums[i - 1];
            pref[i] = pref[i - 1];
            if (last[a[i]] == 0) {
                pref[i] += (a[i] % 2 == 0 ? 1 : -1);
                last[a[i]] = i;
            }
        }
        build(0, n, 0);
        for (int i = 1; i <= n; i++) {
            last[a[i]] = 0;
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (last[a[i]] != 0) {
                int val = (a[i] % 2 == 0 ? 1 : -1);
                upd(0, n, last[a[i]], i - 1, 0, -val);
            }
            last[a[i]] = i;
            j = -1;
            query(0, n, 0, i, 0, pref[i]);
            if (j != -1) {
                ans = max(ans, i - j);
            }
        }
        for (int i = 1; i <= n; i++) {
            last[a[i]] = 0;
        }
        return ans;
    }
};
