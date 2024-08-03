//https://www.spoj.com/problems/MOZHSLS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

string a;
long long segtree[3][3][4 * N];
long long ans[3][3];
long long temp[3][3];

void query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        temp[0][0] = segtree[0][0][node];
        temp[0][1] = segtree[0][1][node] + ans[0][0] * segtree[1][1][node];
        temp[0][2] = segtree[0][2][node] + ans[0][0] * segtree[1][2][node] + ans[0][1] * segtree[2][2][node];
        ans[0][0] += temp[0][0];
        ans[0][1] += temp[0][1];
        ans[0][2] += temp[0][2];
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1);
    query(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        if (a[l] == 's') {
            segtree[0][0][node] = 1;
            segtree[2][2][node] = 1;
        } else if (a[l] == 'm') {
            segtree[1][1][node] = 1;
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[0][0][node] = segtree[0][0][2 * node + 1] + segtree[0][0][2 * node + 2];
    segtree[0][1][node] = segtree[0][1][2 * node + 1] + segtree[0][1][2 * node + 2] +
                          segtree[0][0][2 * node + 1] * segtree[1][1][2 * node + 2];
    segtree[0][2][node] = segtree[0][2][2 * node + 1] + segtree[0][2][2 * node + 2] +
                          segtree[0][0][2 * node + 1] * segtree[1][2][2 * node + 2] +
                          segtree[0][1][2 * node + 1] * segtree[2][2][2 * node + 2];
    segtree[1][1][node] = segtree[1][1][2 * node + 1] + segtree[1][1][2 * node + 2];
    segtree[1][2][node] = segtree[1][2][2 * node + 1] + segtree[1][2][2 * node + 2] +
                          segtree[1][1][2 * node + 1] * segtree[2][2][2 * node + 2];
    segtree[2][2][node] = segtree[2][2][2 * node + 1] + segtree[2][2][2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> a;
    n = a.size();
    cin >> q;
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        query(0, n - 1, l, r, 0);
        cout << ans[0][2] << endl;
        ans[0][0] = 0;
        ans[0][1] = 0;
        ans[0][2] = 0;
    }

    return 0;
}
