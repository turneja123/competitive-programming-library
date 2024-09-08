//https://leetcode.com/problems/maximum-strong-pair-xor-ii/description/
const int MAX = 1e7 + 5;
struct Node {
    int left;
    int right;
    int val;
    Node() : left(-1), right(-1), val(0) {}
};
Node nodes[MAX];
class Solution {
public:
    int idx = 0;
    int query(int node, int d, int val, int ans) {
        if (d == -1) {
            return ans;
        }
        int c = val & (1 << d);
        if (c == 0) {
            if (nodes[node].right != -1 && nodes[nodes[node].right].val > 0) {
                return query(nodes[node].right, d - 1, val, ans ^ (1 << d));
            } else {
                return query(nodes[node].left, d - 1, val, ans);
            }
        } else {
            if (nodes[node].left != -1 && nodes[nodes[node].left].val > 0) {
                return query(nodes[node].left, d - 1, val, ans ^ (1 << d));
            } else {
                return query(nodes[node].right, d - 1, val, ans);
            }
        }
    }

    void add(int node, int d, int val, int sgn) {
        if (d < 0) {
            nodes[node].val += sgn;
            return;
        }
        int c = val & (1 << d);
        if (c == 0) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].left, d - 1, val, sgn);
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node();
            }
            add(nodes[node].right, d - 1, val, sgn);
        }
        nodes[node].val = 0;
        if (nodes[node].left != -1) {
            nodes[node].val += nodes[nodes[node].left].val;
        }
        if (nodes[node].right != -1) {
            nodes[node].val += nodes[nodes[node].right].val;
        }
    }
    int maximumStrongPairXor(vector<int>& nums) {
        nodes[idx++] = Node();
        sort(nums.begin(), nums.end());
        int l = 0, n = nums.size(), ans = 0;
        for (int i = 0; i < n; i++) {
            while (nums[i] - nums[l] > nums[l]) {
                add(0, 20, nums[l], -1);
                l++;
            }
            add(0, 20, nums[i], 1);
            ans = max(ans, query(0, 20, nums[i], 0));
        }
        return ans;
    }
};
