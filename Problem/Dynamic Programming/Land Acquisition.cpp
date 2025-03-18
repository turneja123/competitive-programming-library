//https://www.spoj.com/problems/ACQUIRE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int L = 0, R = 1e6 + 5;

const int MAX = 1e6;
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
    Node() : line(0, INF), left(-1), right(-1) {}
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


int main() {
    IOS;
    nodes[idx++] = Node();
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    vector<long long> dp(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    int last = -1;
    vector<pair<int, int>> b;
    for (int i = n - 1; i >= 0; i--) {
        if (last >= a[i].second) {
            continue;
        }
        last = a[i].second;
        b.push_back(a[i]);
    }
    reverse(b.begin(), b.end());
    a = b;
    n = a.size();
    Line cur = Line(a.back().first, 0);
    add(0, R - 1, 0, cur);
    long long ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = query(0, R - 1, 0, a[i].second);
        if (i != 0) {
            Line cur = Line(a[i - 1].first, dp[i]);
            add(0, R - 1, 0, cur);
        }
        ans = dp[i];
    }
    cout << ans;

    return 0;
}
