//https://leetcode.com/contest/biweekly-contest-131/problems/block-placement-queries/
class Solution {
public:
    int segtree[400005];

    int rmq(int l, int r, int lq, int rq, int node) {
        if (lq <= l && rq >= r) {
            return segtree[node];
        }

        if (l > rq || r < lq) {
            return 0;
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


    vector<bool> getResults(vector<vector<int>>& queries) {
        set<int> st;
        int n = 100000;
        st.insert(0); st.insert(n);
        update(0, n - 1, 0, n, 0);
        vector<bool> ans;
        for (int i = 0; i < queries.size(); i++) {
            if (queries[i][0] == 1) {
                int x = queries[i][1];
                auto it = st.upper_bound(x);
                it--;
                int l = *it;
                it++;
                int r = *it;
                update(0, n - 1, l, x - l, 0);
                update(0, n - 1, x, r - x, 0);
                st.insert(x);
            } else {
                int r = queries[i][1], sz = queries[i][2];
                int mx = rmq(0, n - 1, 0, r - sz, 0);
                if (mx >= sz) {
                    ans.push_back(true);
                } else {
                    ans.push_back(false);
                }
            }
        }
        return ans;
    }
};
