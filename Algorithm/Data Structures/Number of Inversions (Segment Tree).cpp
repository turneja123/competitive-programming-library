//https://www.spoj.com/problems/INVCNT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int segtree[4 * N];
pair<int, int> comp[N];
int pos[N];

int query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) +
               query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = 0;
}

int main() {
    IOS;
    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            comp[i] = make_pair(a[i], i);
        }
        sort(comp, comp + n);
        int m = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && comp[i].first > comp[i - 1].first) {
                m++;
            }
            pos[comp[i].second] = m;
        }
        m++;
        build(0, m - 1, 0);
        for (int i = 0; i < n; i++) {
            int ind = pos[i];
            if (ind < m - 1) {
                ans += query(0, m - 1, ind + 1, m - 1, 0);
            }
            update(0, m - 1, ind, 1, 0);
        }
        cout << ans << endl;
    }
    return 0;
}
