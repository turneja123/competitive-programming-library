//https://www.spoj.com/problems/MORIA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int R = 1e9 + 5;

const int MAX = 1e7;
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
    int t;
    cin >> t;
    long long L = 2000;
    while (t--) {
        nodes[idx++] = Node();
        int n;
        cin >> n;
        Line cur = Line(0, 0);
        add(0, R - 1, 0, cur);
        vector<long long> a(n), pref(n);
        vector<long long> dp(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
            dp[i] = query(0, R - 1, 0, pref[i]) + pref[i] * pref[i] - 2 * pref[i] * L + L * L;
            Line cur = Line(-2 * pref[i], pref[i] * pref[i] + 2 * pref[i] * L + dp[i]);
            add(0, R - 1, 0, cur);
        }
        cout << dp[n - 1] << endl;
        idx = 0;
    }
    return 0;
}
