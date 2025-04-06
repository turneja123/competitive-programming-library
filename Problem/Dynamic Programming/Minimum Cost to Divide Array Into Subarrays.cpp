//https://leetcode.com/contest/biweekly-contest-153/problems/minimum-cost-to-divide-array-into-subarrays/
const int MAX = 1e7;
const long long INF = 2e18;
const int L = -(2e6 + 5), R = 2e6 + 5;

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
    Node() : line(0, INF), left(-1), right(-1) {}
};

Node nodes[MAX];

class Solution {
public:
    int idx = 0;

    void add(int l, int r, int node, Line cur) {
        if (l > r) {
            return;
        }
        int mid = (l + r) / 2;
        if (r - l == 1 && mid == r) {
            mid--;
        }
        bool lf = cur.f(l) < nodes[node].line.f(l);
        bool md = cur.f(mid) < nodes[node].line.f(mid);
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
            return INF;
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
            ans = min(ans, query(l, mid, nodes[node].left, x));
        }
        if (x > mid && nodes[node].right != -1) {
            ans = min(ans, query(mid + 1, r, nodes[node].right, x));
        }
        return ans;
    }

    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        vector<long long> pref_nums(n), pref_cost(n);
        for (int i = 0; i < n; i++) {
            pref_nums[i] = (i == 0 ? nums[i] : pref_nums[i - 1] + nums[i]);
            pref_cost[i] = (i == 0 ? cost[i] : pref_cost[i - 1] + cost[i]);
        }
        vector<bool> seen(n + 1, false);
        seen[0] = true;
        idx++;
        for (int j = 1; j <= n; j++) {
            nodes[idx++] = Node();
        }
        long long ans = INF;
        for (int i = 0; i < n; i++) {
            for (int j = n; j > 0; j--) {
                if (!seen[j - 1]) {
                    continue;
                }
                long long dp = 0;
                if (j == 1) {
                    dp = pref_cost[i] * (pref_nums[i] + j * k);

                } else {
                    dp = pref_cost[i] * (pref_nums[i] + j * k) + query(L, R, j - 1, (pref_nums[i] + j * k));

                }
                Line cur = Line(-pref_cost[i], dp);
                add(L, R, j, cur);
                if (i == n - 1) {
                    ans = min(ans, dp);
                }
                seen[j] = true;
            }
        }
        idx = 0;
        return ans;
    }
};
