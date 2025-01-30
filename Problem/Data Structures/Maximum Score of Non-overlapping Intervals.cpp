//https://leetcode.com/contest/weekly-contest-431/problems/maximum-score-of-non-overlapping-intervals/
const int N = 1e5 + 5;
const long long INF = 1e18;

struct Node {
    vector<long long> val;
    Node() {
        val.resize(5, INF);
    }
    Node(vector<long long> x) {
        val = x;
    }
};

Node segtree[4][4 * N];

class Solution {
public:

    vector<long long> combine(vector<long long> left, vector<long long> right) {
        for (int i = 0; i < 5; i++) {
            if (left[i] < right[i]) {
                return left;
            }
            if (left[i] > right[i]) {
                return right;
            }
        }
        return left;
    }

    vector<long long> query(int l, int r, int lq, int rq, int node, int n) {
        if (l > rq || r < lq) {
            vector<long long> sentinel;
            sentinel.assign(5, INF);
            return sentinel;
        }

        if (lq <= l && rq >= r) {
            return segtree[n][node].val;
        }

        int mid = (l + r) / 2;
        return combine(query(l, mid, lq, rq, 2 * node + 1, n), query(mid + 1, r, lq, rq, 2 * node + 2, n));
    }

    void update(int l, int r, int ind, vector<long long> &val, int node, int n) {
        if (l == r) {
            segtree[n][node].val = combine(val, segtree[n][node].val);
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, val, 2 * node + 1, n);
        } else {
            update(mid + 1, r, ind, val, 2 * node + 2, n);
        }
        segtree[n][node].val = combine(segtree[n][2 * node + 1].val, segtree[n][2 * node + 2].val);
    }


    void build(int l, int r, int node, int n) {
        if (l > r) {
            return;
        }
        if (l == r) {
            segtree[n][node] = Node();
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1, n);
        build(mid + 1, r, 2 * node + 2, n);
        segtree[n][node].val = combine(segtree[n][2 * node + 1].val, segtree[n][2 * node + 2].val);
    }



    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        set<int> st;
        int n = intervals.size();
        for (int i = 0; i < n; i++) {
            st.insert(intervals[i][0]);
            st.insert(intervals[i][1]);
        }
        int m = 0;
        map<int, int> compr;
        for (int x : st) {
            compr[x] = m++;
        }
        vector<tuple<int, int, int, int>> a;
        for (int i = 0; i < n; i++) {
            intervals[i][0] = compr[intervals[i][0]];
            intervals[i][1] = compr[intervals[i][1]];
            a.push_back(make_tuple(intervals[i][0], intervals[i][1], intervals[i][2], i));
        }
        sort(a.begin(), a.end());
        for (int j = 0; j < 4; j++) {
            build(0, m - 1, 0, j);
        }

        for (int i = 0; i < n; i++) {
            auto [l, r, wt, ind] = a[i];
            vector<long long> v;
            for (int j = 2; j >= 0; j--) {
                v = query(0, m - 1, 0, l - 1, 0, j);
                if (v[0] != INF) {
                    v[0] -= wt;
                    v[j + 2] = ind;
                    sort(v.begin() + 1, v.end());
                    update(0, m - 1, r, v, 0, j + 1);
                }
            }
            v = {-wt, ind, INF, INF, INF};
            update(0, m - 1, r, v, 0, 0);
        }
        vector<long long> ansll(5, INF);
        for (int j = 0; j < 4; j++) {
            ansll = combine(ansll, query(0, m - 1, 0, m - 1, 0, j));
        }

        vector<int> ans;
        for (int i = 1; i < 5; i++) {
            if (ansll[i] != INF) {
                ans.push_back(ansll[i]);
            }
        }
        return ans;
    }
};
