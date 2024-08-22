//https://leetcode.com/contest/weekly-contest-349/problems/maximum-sum-queries/
class Solution {
public:
    tuple<int, int, int> sortedx[100005];
    tuple<int, int, int> sortedy[100005];
    tuple<int, int, int> queries[100005];

    int y[100005];
    int pos[100005];
    int segtree[400005];

    int rmq(int l, int r, int lq, int rq, int node) {
        if (lq > rq) {
            return -1;
        }

        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return -1;
        }

        int mid = (l + r) / 2;
        return max(rmq(l, mid, lq, rq, 2 * node + 1),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2));
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
        segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    }


    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[node] = get<0>(sortedy[l]) + get<1>(sortedy[l]);
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    vector<int> maximumSumQueries(vector<int>& a, vector<int>& b, vector<vector<int>>& _queries) {
        int n = a.size(), q = _queries.size();
        for (int i = 0; i < q; i++) {
            queries[i] = make_tuple(_queries[i][0], _queries[i][1], i);
        }
        for (int i = 0; i < n; i++) {
            sortedx[i] = make_tuple(a[i], b[i], i);
            sortedy[i] = make_tuple(b[i], a[i], i);
            y[i] = b[i];
        }
        sort(queries, queries + q);
        sort(sortedx, sortedx + n);
        sort(sortedy, sortedy + n);
        sort(y, y + n);
        for (int i = 0; i < n; i++) {
            pos[get<2>(sortedy[i])] = i;
        }
        int l = 0;
        build(0, n - 1, 0);
        vector<int> ans(q);
        for (int i = 0; i < q; i++) {
            int x = get<0>(queries[i]);
            while (l < n && get<0>(sortedx[l]) < x) {
                update(0, n - 1, pos[get<2>(sortedx[l])], -1, 0);
                l++;
            }
            int ind = lower_bound(y, y + n, get<1>(queries[i])) - y;
            ans[get<2>(queries[i])] = rmq(0, n - 1, ind, n - 1, 0);
        }
        return ans;
    }
};
