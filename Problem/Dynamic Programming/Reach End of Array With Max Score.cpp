//https://leetcode.com/contest/weekly-contest-414/problems/reach-end-of-array-with-max-score/
const int L = 0, R = 1e5 + 5;
const int MAX = 3e6;
const long long INF = 2e18;

struct Line {
    long long k, b;
    long long f(long long x) {
        return k * x + b;
    }
    Line(long long k, long long b) : k(k), b(b) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, -INF), left(-1), right(-1) {}
};

Node nodes[MAX];
class Solution {
public:
    int idx = 0;
    long long dp[100005];
    void add(int l, int r, int node, Line cur) {
        if (l > r) {
            return;
        }
        int mid = (l + r) / 2;
        if (r - l == 1 && mid == r) {
            mid--;
        }
        bool lf = cur.f(l) > nodes[node].line.f(l);
        bool md = cur.f(mid) > nodes[node].line.f(mid);
        if (md) {
            swap(nodes[node].line, cur);
        }
        if (l == r) {
            return;
        }
        if (lf != md) {
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node(cur);
            } else {
                add(l, mid, nodes[node].left, cur);
            }
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node(cur);
            } else {
                add(mid + 1, r, nodes[node].right, cur);
            }
        }
        return;
    }

    long long query(int l, int r, int node, long long x) {
        if (l > r) {
            return -INF;
        }
        int mid = (l + r) / 2;
        if (r - l == 1 && mid == r) {
            mid--;
        }
        long long ans = nodes[node].line.f(x);
        if (l == r) {
            return ans;
        }
        if (x <= mid && nodes[node].left != -1) {
            ans = max(ans, query(l, mid, nodes[node].left, x));
        }
        if (x > mid && nodes[node].right != -1) {
            ans = max(ans, query(mid + 1, r, nodes[node].right, x));
        }
        return ans;
    }


    long long findMaximumScore(vector<int>& nums) {
        nodes[idx++] = Node();
        dp[0] = 0;
        Line cur = Line(nums[0], -nums[0] * 0 + dp[0]);
        add(L, R, 0, cur);
        for (int i = 1; i < nums.size(); i++) {
            dp[i] = query(L, R, 0, i);
            cur = Line(nums[i], (long long)-nums[i] * i + dp[i]);
            add(L, R, 0, cur);
        }
        return dp[nums.size() - 1];
    }
};
