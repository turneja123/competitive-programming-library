//https://atcoder.jp/contests/abc378/tasks/abc378_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];

long long seg_sum[4 * N];
long long seg_cnt[4 * N];

long long get_sum(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return seg_sum[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return get_sum(l, mid, lq, rq, 2 * node + 1) + get_sum(mid + 1, r, lq, rq, 2 * node + 2);
}

long long get_cnt(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return seg_cnt[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return get_cnt(l, mid, lq, rq, 2 * node + 1) + get_cnt(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        seg_sum[node] += ind;
        seg_cnt[node]++;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    seg_sum[node] = seg_sum[2 * node + 1] + seg_sum[2 * node + 2];
    seg_cnt[node] = seg_cnt[2 * node + 1] + seg_cnt[2 * node + 2];
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    long long pref = 0;
    for (int i = 0; i < n; i++) {
        pref = (pref + a[i]) % m;
        ans += pref + pref * get_cnt(0, m - 1, 0, pref, 0) - get_sum(0, m - 1, 0, pref, 0);
        if (pref < m - 1) {
            ans += (pref + m) * get_cnt(0, m - 1, pref + 1, m - 1, 0) - get_sum(0, m - 1, pref + 1, m - 1, 0);
        }
        update(0, m - 1, pref, 0);
    }
    cout << ans;

    return 0;
}
