//https://leetcode.com/contest/biweekly-contest-150/problems/separate-squares-ii/
const int R = 2e9 + 5;
const int MAX = 2e7 + 5;

struct Node {
    int val;
    int ct;
    int lazy;
    int left;
    int right;
    Node() : val(0), ct(0), lazy(0), left(-1), right(-1) {}
    Node(int ct) : val(0), ct(ct), lazy(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

class Solution {
public:
    vector<tuple<int, int, int, int>> event;

    void compose(int parent, int node) {
        nodes[node].lazy += nodes[parent].lazy;
    }

    void apply(int node, int l, int r) {
        if (nodes[node].lazy) {
            nodes[node].val += nodes[node].lazy;
        }
        if (l != r) {
            int mid = ((long long)l + r) / 2;
            if (nodes[node].left == -1) {
                nodes[node].left = idx;
                nodes[idx++] = Node(mid - l + 1);
            }
            compose(node, nodes[node].left);
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node(r - mid);
            }
            compose(node, nodes[node].right);
        }
        nodes[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (lq <= l && rq >= r) {
            nodes[node].lazy += val;
            return;
        }
        int mid = ((long long)l + r) / 2;
        apply(node, l, r);

        incUpdate(nodes[node].left, l, mid, lq, rq, val);
        incUpdate(nodes[node].right, mid + 1, r, lq, rq, val);

        apply(nodes[node].left, l, mid);
        apply(nodes[node].right, mid + 1, r);
        if (nodes[nodes[node].left].val < nodes[nodes[node].right].val) {
            nodes[node].val = nodes[nodes[node].left].val;
            nodes[node].ct = nodes[nodes[node].left].ct;
        } else if (nodes[nodes[node].left].val > nodes[nodes[node].right].val) {
            nodes[node].val = nodes[nodes[node].right].val;
            nodes[node].ct = nodes[nodes[node].right].ct;
        } else {
            nodes[node].val = nodes[nodes[node].left].val;
            nodes[node].ct = nodes[nodes[node].left].ct + nodes[nodes[node].right].ct;
        }
        return;
    }

    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();
        nodes[idx++] = Node(R);
        for (int i = 0; i < n; i++) {
            int x0, y0, x1, y1;
            x0 = squares[i][0], y0 = squares[i][1], x1 = x0 + squares[i][2], y1 = y0 + squares[i][2];
            event.push_back(make_tuple(y0, x0, x1, 1));
            event.push_back(make_tuple(y1, x0, x1, -1));
        }
        sort(event.begin(), event.end());
        long long tot = 0; int last = get<0>(event[0]);
        for (int i = 0; i < 2 * n; i++) {
            auto [y, x0, x1, add] = event[i];
            tot += (long long)(y - last) * (R - nodes[0].ct);
            incUpdate(0, 0, R - 1, x0, x1 - 1, add);
            last = y;
        }
        idx = 0;
        nodes[idx++] = Node(R);
        long long cur = 0;
        long double need = (long double)tot / (long double)2.0;
        last = get<0>(event[0]);
        for (int i = 0; i < 2 * n; i++) {
            auto [y, x0, x1, add] = event[i];
            cur += (long long)(y - last) * (R - nodes[0].ct);
            if ((long double)cur >= need) {
                cur -= (long long)(y - last) * (R - nodes[0].ct);
                long double lf = 0.0, rt = y - last, add = 0.0;
                for (int j = 0; j < 1000; j++) {
                    long double mid = (lf + rt) / (long double)2.0;
                    if ((long double)(R - nodes[0].ct) * mid + (long double)cur >= need) {
                        add = mid;
                        rt = mid;
                    } else {
                        lf = mid;
                    }
                }
                idx = 0;
                return (long double)last + add;
            }
            incUpdate(0, 0, R - 1, x0, x1 - 1, add);
            last = y;
        }
        idx = 0;
        return 0;
    }
};
