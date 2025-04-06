//https://dmoj.ca/problem/coci18c4p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const double INF = 1e18;
const int MAX = 1e6;

long long a[N];
pair<long double, int> dp[N];

struct Line {
    double k, b; int j;
    pair<double, int> f(double x) {
        return make_pair(k * x + b, j);
    }
    Line(double k, double b, int j) : k(k), b(b), j(j) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, -INF, 0), left(-1), right(-1) {}
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

pair<double, int> query(int l, int r, int node, int x) {
    if (l > r) {
        return make_pair(-INF, 0);
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    pair<double, int> ans = nodes[node].line.f((double)x);
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

pair<double, int> calc(int n, double cost) {
    idx = 0;
    nodes[idx++] = Node();
    Line line((double)1.0 / (double)n, 0, 0);
    add(0, N - 1, 0, line);
    for (int i = 1; i <= n; i++) {
        pair<double, int> q = query(0, N - 1, 0, i);
        dp[i] = make_pair(q.first - cost, q.second + 1);
        if (i != n) {
            Line line = Line((double)1.0 / (double)(n - i), dp[i].first - (double)i / (double)(n - i), dp[i].second);
            add(0, N - 1, 0, line);
        }
        /*for (int j = i - 1; j >= 0; j--) {
            dp[i] = max(dp[i], make_pair(dp[j].first - cost + (long double)(i - j) / (long double)(n - j), dp[j].second + 1));
        }*/
    }
    return dp[n];
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, k;
    cin >> n >> k;
    double l = 0, r = 50, opt = 0;
    for (int i = 0; i < 40; i++) {
        double mid = (l + r) / 2;
        if (calc(n, mid).second >= k) {
            opt = mid;
            l = mid;
        } else {
            r = mid;
        }
    }
    double ans = calc(n, opt).first + opt * k;
    cout << ans;
    return 0;
}
