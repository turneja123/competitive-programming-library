//https://atcoder.jp/contests/abc368/tasks/abc368_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N], b[N];

set<int> st;

long long segtree[4 * N];

long long query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, ll val, int node) {
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
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (b[i] != 1) {
            st.insert(i);
        }
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j; long long x;
            cin >> j >> x;
            j--;
            a[j] = x;
            update(0, n - 1, j, x, 0);
        } else if (t == 2) {
            int j; long long x;
            cin >> j >> x;
            j--;
            if (b[j] != 1) {
                st.erase(j);
            }
            b[j] = x;
            if (b[j] != 1) {
                st.insert(j);
            }
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            long long ans = a[l];
            l++;
            if (st.empty()) {
                ans += query(0, n - 1, l, r, 0);
                cout << ans << endl;
            } else {
                int last = l;
                auto it = st.lower_bound(last);
                while (it != st.end() && *it <= r) {
                    ans += query(0, n - 1, last, (*it) - 1, 0);
                    ans = max(ans + a[*it], ans * b[*it]);
                    last = (*it) + 1;
                    it = st.lower_bound(last);
                }
                ans += query(0, n - 1, last, r, 0);
                cout << ans << endl;
            }
        }
    }

    return 0;
}
