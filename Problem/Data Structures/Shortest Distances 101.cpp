//https://www.codechef.com/problems/DATA101
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 25;

int a[N];
int up[K][N];

int segtree[4 * N];

int ind = N, mx = -N;

void traverse(int l, int r, int node) {
    if (l == r) {
        ind = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] >= segtree[2 * node + 2]) {
        traverse(l, mid, 2 * node + 1);
    } else {
        traverse(mid + 1, r, 2 * node + 2);
    }
    return;
}

void rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        if (segtree[node] <= mx) {
            return;
        }
        mx = segtree[node];
        traverse(l, r, node);
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    rmq(l, mid, lq, rq, 2 * node + 1);
    rmq(mid + 1, r, lq, rq, 2 * node + 2);
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
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
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
            a[i] += i;
        }
        build(0, n - 1, 0);

        for (int i = 0; i < n; i++) {
            ind = N, mx = -N;
            rmq(0, n - 1, i, a[i], 0);
            up[0][i] = ind;
        }
        for (int k = 1; k < 25; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            if (a[l] >= r) {
                cout << 1 << endl;
                continue;
            }
            int ans = 0, cur = l;
            for (int k = 24; k >= 0; k--) {
                if (a[cur] >= r) {
                    break;
                }
                int nx = up[k][cur];
                if (a[nx] >= r) {
                    continue;
                }
                ans += 1 << k;
                cur = nx;
            }
            if (a[cur] >= r) {
                cout << ans + 1 << endl;
            } else if (a[up[0][cur]] >= r) {
                cout << ans + 2 << endl;
            } else {
                cout << -1 << endl;
            }
        }

    }

    return 0;
}
