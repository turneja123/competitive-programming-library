//https://leetcode.com/contest/weekly-contest-409/problems/shortest-distance-after-road-addition-queries-ii/
class Solution {
public:
    int segtree[400005];
    int setVal[400005];
    bool setValid[400005];

    void compose(int parent, int child) {
        if (setValid[parent]) {
            setValid[child] = 1;
            setVal[child] = setVal[parent];
        }
    }

    void apply(int node, int l, int r) {
        if (setValid[node]) {
            segtree[node] = (r - l + 1) * setVal[node];
        }
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        setValid[node] = false;
    }

    void setUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            setValid[node] = true;
            setVal[node] = val;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        setUpdate(node * 2 + 1, l, mid, lq, rq, val);
        setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    }

    int getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node];
        }
        int mid = (l + r) / 2;
        return getSum(l, mid, lq, rq, 2 * node + 1) +
               getSum(mid + 1, r, lq, rq, 2 * node + 2);
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = 1;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, node * 2 + 1);
        build(mid + 1, r, node * 2 + 2);
        segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
    }

    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        build(0, n - 1, 0);
        vector<int> ans;
        for (int i = 0; i < queries.size(); i++) {
            setUpdate(0, 0, n - 1, queries[i][0] + 1, queries[i][1] - 1, 0);
            ans.push_back(getSum(0, n - 1, 1, n - 1, 0));
        }
        return ans;
    }
};
