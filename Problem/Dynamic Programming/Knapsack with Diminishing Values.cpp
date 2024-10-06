//https://atcoder.jp/contests/abc373/tasks/abc373_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int L = -1e9 - 5, R = 1e9 + 5;
const int MAX = 1e7;
const long long INF = 2e18;

pair<long long, long long> a[N];

long long dp[N];
long long dp_next[N];
bool has[N];
bool upd[N];

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
int idx = 0;
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

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i <= m; i++) {
        dp[i] = -1;
    }
    dp[0] = 0;
    /*for (int i = 0; i < n; i++) {
        for (int j = m; j > 0; j--) {
            for (int add = 1; add * wt[i] <= j; add++) {
                if (dp[j - add * wt[i]] == -1) {
                    continue;
                }
                long long k = j / wt[i], ki = k - add;
                long long cur = k * x[i] - k * k - (long long)ki * (x[i] - 2 * k) - ki * ki + dp[j - add * wt[i]];
                dp[j] = max(dp[j], cur);
            }
        }
    }*/
    sort(a, a + n);
    nodes[idx++] = Node();
    has[0] = true;
    Line cur(-0, -0 * 0 + dp[0]);
    add(L + 1, R - 1, 0, cur);
    for (int i = 0; i < n; i++) {
        long long x = a[i].second, wt = a[i].first;
        idx = 0;
        for (int j = 0; j < wt; j++) {
            nodes[idx++] = Node();
            has[j] = false;
        }
        Line cur(-0, -0 * 0 + dp[0]);
        add(L + 1, R - 1, 0, cur);
        has[0] = true;
        for (int j = 1; j <= m; j++) {
            if (has[j % wt]) {
                long long k = j / wt;
                long long cur = k * x - k * k + query(L + 1, R - 1, j % wt, x - 2 * k);
                if (cur >= 0) {
                    dp_next[j] = cur;
                }
            }
            if (dp[j] != -1) {
                has[j % wt] = true;
                long long k = j / wt;
                Line cur(-k, -k * k + dp[j]);
                add(L + 1, R - 1, j % wt, cur);
            }
        }
        for (int j = 1; j <= m; j++) {
            dp[j] = max(dp[j], dp_next[j]);
        }

    }
    long long ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;


    return 0;
}
