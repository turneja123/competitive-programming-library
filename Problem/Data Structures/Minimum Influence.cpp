//https://codeforces.com/contest/2230/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const ll INF = 1e18;

struct People {
    int tp;
    int tc;
    int d;
    int i;
};

ll ans[N];
ll b[N];
ll segtree[2][4 * N];
vector<pair<int, int>> items;

ll rmq(int t, int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || lq > rq) {
        return INF;
    }

    if (lq <= l && rq >= r) {
        return segtree[t][node];
    }


    int mid = (l + r) / 2;
    return min(rmq(t, l, mid, lq, rq, 2 * node + 1),
               rmq(t, mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        b[l] = val;
        segtree[0][node] = b[l];
        segtree[1][node] = items[l].first + b[l];
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[0][node] = min(segtree[0][2 * node + 1], segtree[0][2 * node + 2]);
    segtree[1][node] = min(segtree[1][2 * node + 1], segtree[1][2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[0][node] = b[l];
        segtree[1][node] = items[l].first + b[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[0][node] = min(segtree[0][2 * node + 1], segtree[0][2 * node + 2]);
    segtree[1][node] = min(segtree[1][2 * node + 1], segtree[1][2 * node + 2]);
}


int main() {
    IOS;
    int n, m;
    cin >> n;
    items.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].first;
        b[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> items[i].second;
    }
    sort(items.begin(), items.end());
    cin >> m;
    vector<People> a(m);
    for (int i = 0; i < m; i++) {
        a[i].i = i;
        ans[i] = INF;
        cin >> a[i].tp;
    }
    for (int i = 0; i < m; i++) {
        cin >> a[i].tc;
    }
    for (int i = 0; i < m; i++) {
        cin >> a[i].d;
    }

    sort(a.begin(), a.end(), [&](auto x, auto y) {return x.tc < y.tc;});
    build(0, n - 1, 0);
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({items[i].second, i});
    }

    for (int i = m - 1; i >= 0; i--) {
        auto [tp, tc, d, j] = a[i];
        while (pq.size() && pq.top().first >= tc) {
            auto [_, ind] = pq.top();
            pq.pop();
            update(0, n - 1, ind, items[ind].second, 0);
        }

        int l = 0, r = n - 1, spl = -1;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (items[mid].first < tp) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[j] = min(ans[j], rmq(0, 0, n - 1, 0, spl, 0));
        int L = spl + 1;

        l = spl + 1; r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (items[mid].first < tp + d) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[j] = min(ans[j], rmq(1, 0, n - 1, L, spl, 0));

        L = spl + 1;
        ans[j] = min(ans[j], rmq(0, 0, n - 1, L, n - 1, 0) + tp + d);
    }

    while (pq.size()) {
        pq.pop();
    }
    for (int i = 0; i < n; i++) {
        b[i] = items[i].second;
        pq.push({items[i].second, i});
    }
    sort(a.begin(), a.end(), [&](auto x, auto y) {return x.tc + x.d < y.tc + y.d;});
    build(0, n - 1, 0);

    for (int i = 0; i < m; i++) {
        auto [tp, tc, d, j] = a[i];
        while (pq.size() && pq.top().first >= tc + d) {
            auto [_, ind] = pq.top();
            pq.pop();
            update(0, n - 1, ind, 0, 0);
        }

        int l = 0, r = n - 1, spl = -1;

        while (l <= r) {
            int mid = (l + r) / 2;
            if (items[mid].first < tp) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[j] = min(ans[j], rmq(0, 0, n - 1, 0, spl, 0) + tc + d);
        int L = spl + 1;

        l = spl + 1; r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (items[mid].first < tp + d) {
                spl = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans[j] = min(ans[j], rmq(1, 0, n - 1, L, spl, 0) + tc + d);

        L = spl + 1;
        ans[j] = min(ans[j], rmq(0, 0, n - 1, L, n - 1, 0) + tp + d + tc + d);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
