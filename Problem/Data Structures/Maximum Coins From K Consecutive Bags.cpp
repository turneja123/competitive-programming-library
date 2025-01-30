//https://leetcode.com/contest/weekly-contest-431/problems/maximum-coins-from-k-consecutive-bags/
const int R = 1e9 + 5;
const int MAX = 2e7 + 5;

struct Node {
    long long val;
    int lazy;
    int left;
    int right;
    Node() : val(0), lazy(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

class Solution {
public:
    void compose(int parent, int node) {
        nodes[node].lazy |= nodes[parent].lazy;
    }

    void apply(int node, int l, int r) {
        if (nodes[node].lazy) {
            nodes[node].val = (long long)nodes[node].lazy * (r - l + 1);
        }
        if (l != r) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            compose(node, nodes[node].left);
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            compose(node, nodes[node].right);
        }
        nodes[node].lazy = 0;
    }

    void setUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (lq <= l && rq >= r) {
            nodes[node].lazy = val;
            return;
        }
        int mid = (l + r) / 2;
        apply(node, l, r);

        setUpdate(nodes[node].left, l, mid, lq, rq, val);
        setUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

        apply(nodes[node].left, l, mid);
        apply(nodes[node].right, mid + 1, r);
        nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    }

    long long query(int node, int l, int r, int lq, int rq) {
        if (r < lq || l > rq) {
            return 0;
        }
        apply(node, l, r);

        if (lq <= l && rq >= r) {
            return nodes[node].val;
        }

        int mid = (l + r) / 2; long long ans = 0;
        if (nodes[node].left != -1) {
            ans += query(nodes[node].left, l, mid, lq, rq);
        }
        if (nodes[node].right != -1) {
            ans += query(nodes[node].right, mid + 1, r, lq, rq);
        }
        return ans;
    }

    long long maximumCoins(vector<vector<int>>& coins, int k) {
        idx = 0;
        nodes[idx++] = Node();
        int n = coins.size();
        for (int i = 0; i < n; i++) {
            setUpdate(0, 0, R - 1, coins[i][0], coins[i][1], coins[i][2]);
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, query(0, 0, R - 1, max(1, coins[i][1] - k + 1), coins[i][1]));
            ans = max(ans, query(0, 0, R - 1, coins[i][0], min(R - 1, coins[i][0] + k - 1)));
        }
        return ans;
    }
};
