//https://dmoj.ca/problem/utso21p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
vector<pair<int, int>> seg[2][4 * N];

long long ans[N];
long long sum = 0;
int ct = 0;

template <typename T>
struct BIT {
    int n;
    vector<T> t;
    T sum;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
        sum = 0;
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        sum += val;
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    T query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

BIT<int> t_x(N);
BIT<long long> t_y(N);

void add(int node, int l, int r, int lq, int rq, int val, int f) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        if (val == -1) {
            seg[0][node].push_back(make_pair(-1, f));
        } else {
            seg[1][node].push_back(make_pair(val, f));
        }
        return;
    }
    int mid = (l + r) / 2;
    add(node * 2 + 1, l, mid, lq, rq, val, f);
    add(node * 2 + 2, mid + 1, r, lq, rq, val, f);
}

void dfs(int l, int r, int node) {
    if (l > r) {
        return;
    }
    ct += seg[0][node].size();
    for (int i = 0; i < seg[0][node].size(); i++) {
        sum += t_y.query(seg[0][node][i].second + 1);
        t_x.upd(seg[0][node][i].second + 1, 1);
    }
    for (int i = 0; i < seg[1][node].size(); i++) {
        sum += (long long)(t_x.sum - t_x.query(seg[1][node][i].second)) * seg[1][node][i].first;
        t_y.upd(seg[1][node][i].second + 1, seg[1][node][i].first);
    }
    if (l == r) {
        ans[l] = sum + (long long)ct * a[l];
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    ct -= seg[0][node].size();
    for (int i = 0; i < seg[0][node].size(); i++) {
        sum -= t_y.query(seg[0][node][i].second + 1);
        t_x.upd(seg[0][node][i].second + 1, -1);
    }
    for (int i = 0; i < seg[1][node].size(); i++) {
        sum -= (long long)(t_x.sum - t_x.query(seg[1][node][i].second)) * seg[1][node][i].first;
        t_y.upd(seg[1][node][i].second + 1, -seg[1][node][i].first);
    }
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            add(0, 0, n - 1, l, r, x, i);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            add(0, 0, n - 1, l, r, -1, i);
        }
    }
    dfs(0, n - 1, 0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
