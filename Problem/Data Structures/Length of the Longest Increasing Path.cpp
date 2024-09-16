//https://leetcode.com/contest/biweekly-contest-139/problems/length-of-the-longest-increasing-path/
class Solution {
public:
    tuple<int, int, int> a[100005];
    set<int> st;
    map<int, int> pos;
    int segtree[4 * 100005];

    int rmq(int l, int r, int lq, int rq, int node) {
        if (l > rq || r < lq || lq > rq) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return segtree[node];
        }


        int mid = (l + r) / 2;
        return max(rmq(l, mid, lq, rq, 2 * node + 1),
                   rmq(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void update(int l, int r, int ind, int val, int node) {
        if (l == r) {
            segtree[node] = max(segtree[node], val);
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
            segtree[node] = 0;
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    }


    int maxPathLength(vector<vector<int>>& points, int k) {
        int n = points.size();
        int mxx;
        for (int i = 0; i < n; i++) {
            a[i] = make_tuple(points[i][0], points[i][1], i);
            st.insert(points[i][1]);
            if (i == k) {
                mxx = points[i][1];
            }
        }
        sort(a, a + n);
        int j = 0;
        for (auto x : st) {
            pos[x] = j++;
        }
        int ans = 0, flag = 0;
        for (int i = 0; i < n;) {

            int last = get<0>(a[i]);
            vector<int> q;
            int m = i; int seen = 0;
            while (i < n && get<0>(a[i]) == last) {
                int x = get<0>(a[i]), y = get<1>(a[i]), j = get<2>(a[i]);
                int ind = pos[y];
                int mx = rmq(0, n - 1, 0, ind - 1, 0) + 1;
                if (seen && k != j) {
                    mx = 0;
                }
                if (k == j) {
                    seen = 1;
                }
                q.push_back(mx);
                i++;
            }
            for (int p = m; p < i; p++) {
                int x = get<0>(a[p]), y = get<1>(a[p]), j = get<2>(a[p]);
                int ind = pos[y];
                int mx = q[p - m];
                if (k == j && mx == 0) {
                    mx = 1;
                }
                if (y <= mxx && flag) {
                    mx = 0;
                }
                if (k == j) {
                    flag = 1;
                    build(0, n - 1, 0);
                }
                update(0, n - 1, ind, mx, 0);
                if (flag) {
                    ans = max(ans, mx);
                }
            }
        }
        return ans;
    }
};
