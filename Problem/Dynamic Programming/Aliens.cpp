//https://dmoj.ca/problem/ioi16p6io
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int R = 3e6;

const int MAX = 1e6;
const long long INF = 1e18;

pair<long long, int> dp[N];

struct Line {
    long long k, b; int j;
    pair<long long, int> f(long long x) {
        return make_pair(k * x + b, j);
    }
    Line(long long k, long long b, int j) : k(k), b(b), j(j) {}
};

struct Node {
    Line line;
    int left;
    int right;
    Node(Line line) : line(line), left(-1), right(-1) {}
    Node() : line(0, INF, 0), left(-1), right(-1) {}
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

pair<long long, int> query(int l, int r, int node, int x) {
    if (l > r) {
        return make_pair(INF, 0);
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    pair<long long, int> ans = nodes[node].line.f(x);
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

pair<long long, int> calc(int n, long long cost, vector<pair<int, int>> &a) {
    /*for (int i = 0; i < n; i++) {
        dp[i] = make_pair(INF, 0);
        for (int j = i - 1; j >= 0; j--) {
            long long cur = dp[j].first + (long long)(a[i].second - a[j + 1].first + 1) * (a[i].second - a[j + 1].first + 1) + cost;
            if (a[j].second >= a[j + 1].first) {
                cur -= (long long)(a[j].second - a[j + 1].first + 1) * (a[j].second - a[j + 1].first + 1);
            }
            dp[i] = min(dp[i], make_pair(cur, dp[j].second - 1));
        }
        dp[i] = min(dp[i], make_pair((long long)(a[i].second - a[0].first + 1) * (a[i].second - a[0].first + 1) + cost, -1));
    }*/
    idx = 0;
    nodes[idx++] = Node();
    for (int i = 0; i < n; i++) {
        dp[i] = make_pair((long long)(a[i].second - a[0].first + 1) * (a[i].second - a[0].first + 1) + cost, -1);
        if (i != 0) {
            pair<long long, int> qr = query(0, R, 0, 2 * (a[i].second + 1));
            qr.first += cost + (long long)(a[i].second + 1) * (a[i].second + 1);
            qr.second += -1;
            dp[i] = min(dp[i], qr);
        }
        if (i != n - 1) {
            long long overlap = (a[i].second >= a[i + 1].first ? (long long)(a[i].second - a[i + 1].first + 1) * (a[i].second - a[i + 1].first + 1) : 0);
            Line line(-a[i + 1].first, dp[i].first - overlap + (long long)a[i + 1].first * a[i + 1].first, dp[i].second);
            add(0, R, 0, line);

        }
    }
    return dp[n - 1];
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x > y) {
            swap(x, y);
        }
        auto it = mp.find(y);
        if (it == mp.end()) {
            mp[y] = x;
        } else {
            it->second = min(it->second, x);
        }
    }
    stack<pair<int, int>> st;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        int y = it->first, x = it->second;
        while (st.size() && st.top().first >= x) {
            st.pop();
        }
        st.push(make_pair(x, y));
    }
    vector<pair<int, int>> a;
    while (st.size()) {
        a.push_back(st.top());
        st.pop();
    }
    reverse(a.begin(), a.end());
    n = a.size();
    /*vector<long long> dp(n);
    dp[0] = (long long)(a[0].second - a[0].first + 1) * (a[0].second - a[0].first + 1);
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + (a[i].second - a[i].first + 1) * (a[i].second - a[i].first + 1);
        if (a[i - 1].second >= a[i].first) {
            dp[i] -= (long long)(a[i - 1].second - a[i].first + 1) * (a[i - 1].second - a[i].first + 1);
        }
    }
    cout << dp[n - 1];*/

    long long l = 0, r = 1e12, opt = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (-calc(n, mid, a).second >= k) {
            opt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    long long ans = calc(n, opt, a).first - opt * k;
    cout << ans;
    return 0;
}
