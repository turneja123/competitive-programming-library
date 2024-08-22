//https://atcoder.jp/contests/abc247/tasks/abc247_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

int a[N];
int table[2][K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][0][i] = a[i - 1];
        table[1][0][i] = a[i - 1];
    }
    for (int k = 1; k < 18; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[0][k][i] = min(table[0][k - 1][i], table[0][k - 1][i + (1 << (k - 1))]);
            table[1][k][i] = max(table[1][k - 1][i], table[1][k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r, int sgn) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (sgn == 0) {
        return min(table[0][k][l], table[0][k][r - (1 << k) + 1]);
    } else {
        return max(table[1][k][l], table[1][k][r - (1 << k) + 1]);
    }
}

int main() {
    IOS;
    int n, x, y;
    cin >> n >> x >> y;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int l = i, r = n - 1, ly = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int mn = query(i, mid, 0);
            if (mn <= y) {
                r = mid - 1;
                if (mn == y) {
                    ly = mid;
                }
            } else {
                l = mid + 1;
            }
        }
        if (ly == -1) {
            continue;
        }
        l = i, r = n - 1; int ry = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int mn = query(i, mid, 0);
            if (mn >= y) {
                l = mid + 1;
                if (mn == y) {
                    ry = mid;
                }
            } else {
                r = mid - 1;
            }
        }

        l = i, r = n - 1; int lx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int mx = query(i, mid, 1);
            if (mx >= x) {
                r = mid - 1;
                if (mx == x) {
                    lx = mid;
                }
            } else {
                l = mid + 1;
            }
        }
        if (lx == -1) {
            continue;
        }
        l = i, r = n - 1; int rx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int mx = query(i, mid, 1);
            if (mx <= x) {
                l = mid + 1;
                if (mx == x) {
                    rx = mid;
                }
            } else {
                r = mid - 1;
            }
        }
        int L = max(lx, ly), R = min(rx, ry);
        if (L > R) {
            continue;
        }
        ans += R - L + 1;
    }
    cout << ans;

    return 0;
}
