//https://www.spoj.com/problems/VZLA2019K/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int a[N][2];
int segtree[4 * N][2];
bool f = false;

int rmq(int l, int r, int lq, int rq, int node, int n) {
    if (lq <= l && rq >= r) {
        if (segtree[node][n] > 0) {
            f = true;
            return segtree[node][n];
        }
        return -INF;
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    int ans = max(rmq(l, mid, lq, rq, 2 * node + 1, n),
               rmq(mid + 1, r, lq, rq, 2 * node + 2, n));
    if (ans == 0) {
        return -INF;
    }
    return ans;
}

void update(int l, int r, int ind, int val, int node, int n) {
    if (l == r) {
        a[ind][n] = val;
        segtree[node][n] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[node][n] = max(segtree[2 * node + 1][n], segtree[2 * node + 2][n]);
}

int main() {
    IOS;
    int n, d, p, ans = 0;
    cin >> n >> d >> p;
    for (int i = 0; i < n; i++) {
        int c, w; char x;
        cin >> c >> w >> x;
        if (x == 'D') {
            if (d >= w) {
                ans = max(ans, c + rmq(0, p, 0, p, 0, 1));
                ans = max(ans, c + rmq(0, d, 0, d - w, 0, 0));
                if (c > a[w][0]) {
                    update(0, d, w, c, 0, 0);
                }
            }
        } else {
            if (p >= w) {
                ans = max(ans, c + rmq(0, d, 0, d, 0, 0));
                ans = max(ans, c + rmq(0, p, 0, p - w, 0, 1));
                if (c > a[w][1]) {
                    update(0, p, w, c, 0, 1);
                }
            }
        }
    }
    if (!f) {
        cout << "sad:(";
    } else {
        cout << ans;
    }


    return 0;
}
