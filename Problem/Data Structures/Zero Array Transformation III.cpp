//https://leetcode.com/contest/biweekly-contest-144/problems/zero-array-transformation-iii/
const int N = 1e5 + 5;
const int INF = 1e9;
int segtree[4 * N];
int lazy[4 * N];

class Solution {
public:
    static bool comp(vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    }

    void compose(int parent, int child) {
        lazy[child] += lazy[parent];
    }

    void apply(int node, int l, int r) {
        segtree[node] += lazy[node];
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        lazy[node] = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            lazy[node]--;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, lq, rq);
        incUpdate(node * 2 + 2, mid + 1, r, lq, rq);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
    }

    int get(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return INF;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node];
        }
        int mid = (l + r) / 2;
        return min(get(l, mid, lq, rq, 2 * node + 1), get(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node, vector<int> &a) {
        if (l > r) {
            return;
        }
        lazy[node] = 0;
        if (l == r) {
            segtree[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1, a);
        build(mid + 1, r, node * 2 + 2, a);
        segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
    }



    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        build(0, n - 1, 0, nums);
        vector<int> b(n);
        for (int i = 0; i < queries.size(); i++) {
            incUpdate(0, 0, n - 1, queries[i][0], queries[i][1]);
        }
        for (int i = 0; i < n; i++) {
            b[i] = get(0, n - 1, i, i, 0);
            if (b[i] > 0) {
                return -1;
            }
            b[i] = -b[i];
        }
        build(0, n - 1, 0, b);
        sort(queries.begin(), queries.end(), comp);
        int ans = 0;
        for (int i = 0; i < queries.size(); i++) {
            int x = get(0, n - 1, queries[i][0], queries[i][1], 0);
            if (x > 0) {
                ans++;
                incUpdate(0, 0, n - 1, queries[i][0], queries[i][1]);
            }
        }
        return ans;
    }
};
