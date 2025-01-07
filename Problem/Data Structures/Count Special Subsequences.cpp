//https://leetcode.com/contest/weekly-contest-430/problems/count-special-subsequences/
const int N = 1005;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = N * N + 2 * N;
bool seen[N * N + 2 * N];

class Solution {
public:
    int query(int node, int l, int r, int lq, int rq) {
        if (r < lq || l > rq) {
            return 0;
        }
        if (lq <= l && rq >= r) {
            return nodes[node].val;
        }
        int mid = (l + r) / 2, ans = 0;
        if (nodes[node].left != -1) {
            ans += query(nodes[node].left, l, mid, lq, rq);
        }
        if (nodes[node].right != -1) {
            ans += query(nodes[node].right, mid + 1, r, lq, rq);
        }
        return ans;

    }

    void update(int node, int l, int r, int ind, int val) {
        if (l == r) {
            nodes[node].val += val;
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
            nodes[node].val += nodes[nodes[node].left].val;
        }
        if (nodes[node].right != -1) {
            nodes[node].val += nodes[nodes[node].right].val;
        }
    }

    long long numberOfSubsequences(vector<int>& a) {
        int n = a.size();
        // p q r s
        for (int q = 2; q < n; q++) {
            for (int r = q + 2; r < n - 2; r++) {
                int g = __gcd(a[q], a[r]);
                int frac = (a[q] / g) * N + a[r] / g;
                if (!seen[frac]) {
                    seen[frac] = true;
                    nodes[frac] = Node();
                }
                update(frac, 0, n - 1, r, 1);
            }
        }
        long long ans = 0;
        for (int p = 0; p < n; p++) {
            for (int s = p + 6; s < n; s++) {
                int g = __gcd(a[p], a[s]);
                int frac = (a[p] / g) * N + a[s] / g;
                if (seen[frac]) {
                    ans += query(frac, 0, n - 1, 0, s - 2);
                }
            }
            int q = p + 2;
            for (int r = q + 2; r < n - 2; r++) {
                int g = __gcd(a[q], a[r]);
                int frac = (a[q] / g) * N + a[r] / g;
                update(frac, 0, n - 1, r, -1);
            }
        }
        for (int q = 2; q < n; q++) {
            for (int r = q + 2; r < n - 2; r++) {
                int g = __gcd(a[q], a[r]);
                int frac = (a[q] / g) * N + a[r] / g;
                seen[frac] = false;
            }
        }
        idx = N * N + 2 * N;
        return ans;
    }
};
