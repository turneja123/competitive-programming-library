//https://leetcode.com/contest/weekly-contest-427/problems/maximum-area-rectangle-with-point-constraints-ii/
const int R = 8e7 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

class Solution {
public:

    int query(int node, int l, int r, int lq, int rq) {
        if (r < lq || l > rq || lq > rq) {
            return -1;
        }
        if (lq <= l && rq >= r) {
            return nodes[node].val;
        }
        int mid = (l + r) / 2, ans = 0;
        if (nodes[node].left != -1) {
            ans = max(ans, query(nodes[node].left, l, mid, lq, rq));
        }
        if (nodes[node].right != -1) {
            ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq));
        }
        return ans;

    }

    void update(int node, int l, int r, int ind, int val) {
        if (l == r) {
            nodes[node].val = max(nodes[node].val, val);
            return;
        }
        int mid = (l + r) / 2;
        if (ind <= mid) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            update(nodes[node].left, l, mid, ind, val);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            update(nodes[node].right, mid + 1, r, ind, val);
        }
        nodes[node].val = 0;
        if (nodes[node].left != -1) {
            nodes[node].val = max(nodes[node].val, nodes[nodes[node].left].val);
        }
        if (nodes[node].right != -1) {
            nodes[node].val = max(nodes[node].val, nodes[nodes[node].right].val);
        }
    }

    long long maxRectangleArea(vector<int>& x, vector<int>& y) {
        idx = 0;
        nodes[idx++] = Node();

        int n = x.size();
        map<int, vector<int>> mp;
        map<pair<int, int>, vector<int>> st;

        for (int i = 0; i < n; i++) {
            mp[x[i]].push_back(y[i]);
        }
        long long ans = -1;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            vector<int> v = it->second;
            sort(v.begin(), v.end());
            for (int i = 1; i < v.size(); i++) {
                int mx = query(0, 0, R - 1, v[i - 1], v[i]);
                auto f = st.find(make_pair(v[i - 1], v[i]));
                if (f != st.end()) {
                    int x = lower_bound((f->second).begin(), (f->second).end(), mx) - (f->second).begin();
                    if (x < (f->second).size()) {
                        ans = max(ans, (long long)(v[i] - v[i - 1]) * (it->first - (f->second)[x]));
                    }
                }
                st[make_pair(v[i - 1], v[i])].push_back(it->first);
            }
            for (int i = 0; i < v.size(); i++) {
                update(0, 0, R - 1, v[i], it->first);
            }
        }
        return ans;
    }
};
