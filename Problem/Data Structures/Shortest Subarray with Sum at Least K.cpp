//https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k
const long long R = 1e11 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    long long left;
    long long right;
    Node() : val(-MAX), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

class Solution {
public:
    int query(int node, long long l, long long r, long long lq, long long rq) {
        if (r < lq || l > rq) {
            return -MAX;
        }
        if (lq <= l && rq >= r) {
            return nodes[node].val;
        }
        long long mid = (l + r) / 2; int ans = -MAX;
        if (r - l == 1) {
            mid = l;
        }
        if (nodes[node].left != -1) {
            ans = max(ans, query(nodes[node].left, l, mid, lq, rq));
        }
        if (nodes[node].right != -1) {
            ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq));
        }
        return ans;

    }

    void update(int node, long long l, long long r, long long ind, int val) {
        if (l == r) {
            nodes[node].val = max(nodes[node].val, val);
            return;
        }
        long long mid = (l + r) / 2;
        if (r - l == 1) {
            mid = l;
        }
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
        nodes[node].val = -MAX;
        if (nodes[node].left != -1) {
            nodes[node].val = max(nodes[node].val, nodes[nodes[node].left].val);
        }
        if (nodes[node].right != -1) {
            nodes[node].val = max(nodes[node].val, nodes[nodes[node].right].val);
        }
    }


    int shortestSubarray(vector<int>& nums, int k) {
        idx = 0;
        nodes[idx++] = Node();
        long long sum = 0;
        update(0, -R, R, 0, -1);
        int ans = MAX;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            int l = query(0, -R, R, -R, sum - k);
            if (l != -MAX) {
                ans = min(ans, i - l);
            }
            update(0, -R, R, sum, i);
        }
        if (ans == MAX) {
            ans = -1;
        }
        return ans;
    }
};
