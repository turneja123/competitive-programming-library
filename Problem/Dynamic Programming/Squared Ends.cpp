//https://csacademy.com/contest/archive/task/squared-ends/statement/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int L = 0, R = 1e6 + 5;

const int N = 1e4 + 5;
const int K = 105;
const int MAX = 5e6;
const long long INF = 2e18;

long long a[N];
long long dp[N][K];

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
int idx = 0;

void add(int l, int r, int lq, int rq, int node, Line cur) {
    if (l > r || l > rq || r < lq) {
        return;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    if (l >= lq && r <= rq) {
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
                add(l, mid, lq, rq, nodes[node].left, cur);
            }
        } else {
            if (nodes[node].right == -1) {
                nodes[node].right = idx;
                nodes[idx++] = Node(cur);
            } else {
                add(mid + 1, r, lq, rq, nodes[node].right, cur);
            }
        }
        return;
    }
    if (l == r) {
        return;
    }
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(l, mid, lq, rq, nodes[node].left, cur);
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(mid + 1, r, lq, rq, nodes[node].right, cur);
    }

    return;
}

long long query(int l, int r, int lq, int rq, int node, long long x) {
    if (l > r || l > rq || r < lq) {
        return INF;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    if (l >= lq && r <= rq) {
        long long ans = nodes[node].line.f(x);
        if (l == r) {
            return ans;
        }
        if (x <= mid && nodes[node].left != -1) {
            ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
        }
        if (x > mid && nodes[node].right != -1) {
            ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
        }
        return ans;
    }
    long long ans = INF;
    if (max(l, lq) <= min(mid, rq)) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(l, mid, lq, rq, nodes[node].left, x));
    }
    if (max(mid + 1, lq) <= min(r, rq)) {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        ans = min(ans, query(mid + 1, r, lq, rq, nodes[node].right, x));
    }
    return ans;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        nodes[idx++] = Node();
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = min(i, k - 1); j >= 0; j--) {
            if (j == 0) {
                dp[i][j] = (a[i] - a[0]) * (a[i] - a[0]);
            } else {
                dp[i][j] = a[i] * a[i] + query(L, R, L, R, j - 1, a[i]);
            }
            Line line(-2 * a[i + 1], dp[i][j] + a[i + 1] * a[i + 1]);
            add(L, R, L, R, j, line);
        }
    }
    cout << dp[n - 1][k - 1];
    return 0;
}
