//https://leetcode.com/contest/weekly-contest-411/problems/count-substrings-that-satisfy-k-constraint-ii/

struct Node {
    long long val;
    int ct;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1), ct(0) {}
};

Node nodes[10000005];

class Solution {
public:
    int pref[100005];
    int rt[100005];
    long long sumi[100005];

    int idx = 0;
    int root[100005];

    void build(int node, int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) / 2;
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = idx;
        nodes[idx++] = Node();
        build(nodes[node].left, l, mid);
        build(nodes[node].right, mid + 1, r);
        return;
    }

    void update(int node_prev, int node, int l, int r, int ind) {
        if (l == r) {
            nodes[node].ct = nodes[node_prev].ct + 1;
            nodes[node].val = nodes[node_prev].val + ind;
            return;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
            nodes[node].right = nodes[node_prev].right;
            update(nodes[node_prev].left, nodes[node].left, l, mid, ind);
        } else {
            nodes[node].right = idx;
            nodes[idx++] = Node();
            nodes[node].left = nodes[node_prev].left;
            update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind);
        }
        nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
        nodes[node].ct = nodes[nodes[node].left].ct + nodes[nodes[node].right].ct;
        return;
    }

    long long queryVal(int node_l, int node_r, int l, int r, int lq, int rq) {
        if (lq > r || rq < l) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return nodes[node_r].val - nodes[node_l].val;
        }
        int mid = (l + r) / 2;
        return queryVal(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + queryVal(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
    }

    int queryCt(int node_l, int node_r, int l, int r, int lq, int rq) {
        if (lq > r || rq < l) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return nodes[node_r].ct - nodes[node_l].ct;
        }
        int mid = (l + r) / 2;
        return queryCt(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + queryCt(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
    }

    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int add = s[i] - '0';
            pref[i] = ((i == 0) ? add : pref[i - 1] + add);
            sumi[i] = ((i == 0) ? i : sumi[i - 1] + i);
        }
        for (int i = 0; i < n; i++) {
            int l = i, r = n - 1, spl = l;
            while (l <= r) {
                int mid = (l + r) / 2;
                int ct = pref[mid] - ((i == 0) ? 0 : pref[i - 1]);
                if (ct > k && mid - i + 1 - ct > k) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                    spl = mid;
                }
            }
            rt[i] = spl;
        }
        root[0] = idx;
        nodes[idx++] = Node();
        build(root[0], 0, n - 1);
        for (int i = 0; i < n; i++) {
            root[i + 1] = idx;
            nodes[idx++] = Node();
            update(root[i], root[i + 1], 0, n - 1, rt[i]);
        }
        vector<long long> ans;
        for (int i = 0; i < queries.size(); i++) {
            int l = queries[i][0], r = queries[i][1];
            long long tot = queryVal(root[l], root[r + 1], 0, n - 1, 0, n - 1);
            if (r < n - 1) {
                long long sum = queryVal(root[l], root[r + 1], 0, n - 1, r + 1, n - 1);
                long long ct = queryCt(root[l], root[r + 1], 0, n - 1, r + 1, n - 1);
                tot += ct * r - sum;
            }
            tot -= sumi[r] - ((l == 0) ? 0 : sumi[l - 1]) - (r - l + 1);
            ans.push_back(tot);
        }
        return ans;
    }
};
