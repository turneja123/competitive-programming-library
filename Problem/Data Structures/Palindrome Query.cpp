//https://atcoder.jp/contests/abc331/tasks/abc331_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

const long long M = 1e9 + 7;
const long long P = 26, Q = 53;

int a[N];
long long pw_p[N], pw_q[N];
pair<long long, long long> segtree[2][4 * N];

pair<pair<long long, long long>, pair<long long, long long>> ans;

void query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        ans.first.first = (ans.first.first + segtree[0][node].first) % M;
        ans.first.second = (ans.first.second + segtree[0][node].second) % M;
        ans.second.first = (ans.second.first + segtree[1][node].first) % M;
        ans.second.second = (ans.second.second + segtree[1][node].second) % M;
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1);
    query(mid + 1, r, lq, rq, 2 * node + 2);
    return;
}

void update(int l, int r, int ind, int val, int node, int n) {
    if (l == r) {
        segtree[0][node].first = pw_p[l] * val % M;
        segtree[1][node].first = pw_p[n - 1 - l] * val % M;
        segtree[0][node].second = pw_q[l] * val % M;
        segtree[1][node].second = pw_q[n - 1 - l] * val % M;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[0][node].first = (segtree[0][2 * node + 1].first + segtree[0][2 * node + 2].first) % M;
    segtree[1][node].first = (segtree[1][2 * node + 1].first + segtree[1][2 * node + 2].first) % M;
    segtree[0][node].second = (segtree[0][2 * node + 1].second + segtree[0][2 * node + 2].second) % M;
    segtree[1][node].second = (segtree[1][2 * node + 1].second + segtree[1][2 * node + 2].second) % M;
    return;
}


void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[0][node].first = pw_p[l] * a[l] % M;
        segtree[1][node].first = pw_p[n - 1 - l] * a[l] % M;
        segtree[0][node].second = pw_q[l] * a[l] % M;
        segtree[1][node].second = pw_q[n - 1 - l] * a[l] % M;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[0][node].first = (segtree[0][2 * node + 1].first + segtree[0][2 * node + 2].first) % M;
    segtree[1][node].first = (segtree[1][2 * node + 1].first + segtree[1][2 * node + 2].first) % M;
    segtree[0][node].second = (segtree[0][2 * node + 1].second + segtree[0][2 * node + 2].second) % M;
    segtree[1][node].second = (segtree[1][2 * node + 1].second + segtree[1][2 * node + 2].second) % M;
    return;
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - 'a';
        pw_p[i] = ((i == 0) ? 1 : pw_p[i - 1] * P % M);
        pw_q[i] = ((i == 0) ? 1 : pw_q[i - 1] * Q % M);
    }
    build(0, n - 1, 0, n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j; char c;
            cin >> j >> c;
            j--;
            int d = c - 'a';
            update(0, n - 1, j, d, 0, n);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            query(0, n - 1, l, r, 0);
            if (l > n - 1 - r) {
                ans.second.first = ans.second.first * pw_p[l - (n - 1 - r)] % M;
                ans.second.second = ans.second.second * pw_q[l - (n - 1 - r)] % M;
            }
            if (n - 1 - r > l) {
                ans.first.first = ans.first.first * pw_p[n - 1 - r - l] % M;
                ans.first.second = ans.first.second * pw_q[n - 1 - r - l] % M;
            }
            if (ans.first.first == ans.second.first && ans.first.second == ans.second.second) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
            ans = make_pair(make_pair(0, 0), make_pair(0, 0));
        }
    }

    return 0;
}
