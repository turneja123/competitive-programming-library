//https://codeforces.com/contest/2184/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
int segtree[4 * N];

int query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return INF;
    }

    int mid = (l + r) / 2;
    return min(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
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
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
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
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        build(0, n - 1, 0);
        for (int i = 0; i < q; i++) {
            int t, l, r;
            cin >> t >> l >> r;
            if (t == 1) {
                l--;
                update(0, n - 1, l, r, 0);
            } else {
                l--, r--;

                int lf = l, rt = r, spl1 = n;
                while (lf <= rt) {
                    int mid = (lf + rt) / 2;

                    int m = query(0, n - 1, l, mid, 0);
                    if (m <= mid - l) {
                        spl1 = mid;
                        rt = mid - 1;
                    } else {
                        lf = mid + 1;
                    }
                }
                lf = l, rt = r; int spl2 = n;
                while (lf <= rt) {
                    int mid = (lf + rt) / 2;

                    int m = query(0, n - 1, l, mid, 0);
                    if (m < mid - l) {
                        spl2 = mid;
                        rt = mid - 1;
                    } else {
                        lf = mid + 1;
                    }
                }
                int ans = spl1 != spl2;
                cout << ans << endl;
            }
        }
    }

    return 0;
}
