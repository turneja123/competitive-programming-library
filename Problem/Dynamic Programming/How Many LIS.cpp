//https://www.spoj.com/problems/HMLIS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const unsigned long long M = 1e9 + 7;

const int N = 1e5 + 5;

int a[N];
int pos[N];
pair<int, int> compr[N];
pair<int, long long> segtree[4 * N];
pair<int, long long> dp[N];


pair<int, long long> rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return make_pair(0, 0);
    }

    int mid = (l + r) / 2;
    pair<int, long long> lnode = rmq(l, mid, lq, rq, 2 * node + 1), rnode = rmq(mid + 1, r, lq, rq, 2 * node + 2), ans;
    ans.first = max(lnode.first, rnode.first);
    if (lnode.first > rnode.first) {
        ans.second = lnode.second;
    } else if (lnode.first < rnode.first) {
        ans.second = rnode.second;
    } else {
        ans.second = lnode.second + rnode.second;
    }
    return ans;
}

void update(int l, int r, int ind, pair<int, long long> val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node].first = max(segtree[2 * node + 1].first, segtree[2 * node + 2].first);
    if (segtree[2 * node + 1].first > segtree[2 * node + 2].first) {
        segtree[node].second = segtree[2 * node + 1].second;
    } else if (segtree[2 * node + 1].first < segtree[2 * node + 2].first) {
        segtree[node].second = segtree[2 * node + 2].second;
    } else {
        segtree[node].second = segtree[2 * node + 1].second + segtree[2 * node + 2].second;
    }

}
int main() {
	IOS;
	int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i].first = a[i], compr[i].second = i;
    }
    sort(compr, compr + n);
    int m = 0;
    pos[compr[0].second] = m;
    for (int i = 1; i < n; i++) {
        if (compr[i].first > compr[i - 1].first) {
            m++;
        }
        pos[compr[i].second] = m;
    }
    m++;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int ind = pos[i];
        pair<int, long long> cur;
        if (ind == 0) {
            cur = make_pair(1, 1);
        } else {
            cur = rmq(0, m - 1, 0, ind - 1, 0);
            if (cur.first == 0) {
                cur = make_pair(1, 1);
            } else {
                cur.first++;
            }
        }
        if (cur.first == dp[ind].first) {
            dp[ind].second = (dp[ind].second + cur.second) % M;
        } else if (cur.first > dp[ind].first) {
            dp[ind] = cur;
            dp[ind].second %= M;
        }
        update(0, m - 1, ind, dp[ind], 0);
        mx = max(mx, dp[ind].first);
    }
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        if (dp[i].first == mx) {
            ans += dp[i].second;
        }
    }
    cout << mx << " " << ans % M;

	return 0;
}
