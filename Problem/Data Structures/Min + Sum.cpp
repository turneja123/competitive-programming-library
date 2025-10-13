//https://atcoder.jp/contests/abc282/tasks/abc282_h
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;

ll a[N];
ll b[N];
ll pref[N];

ll table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

ll query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

ll query_s(int l, int r) {
    return pref[r] - (l == 0 ? 0 : pref[l - 1]);
}

ll ans = 0;

void calc(int l, int r, ll s) {
    int mid = (l + r) / 2;
    if (l == r) {
        ans += (a[l] + b[l]) <= s;
        return;
    }
    ll mn = a[mid]; ll S = 0;
    for (int i = mid; i >= l; i--) {
        mn = min(mn, a[i]);
        S += b[i];
        int L = mid + 1, R = r, spl = r + 1;
        while (L <= R) {
            int m = (L + R) / 2;
            if (query(mid + 1, m) < mn || mn + S + query_s(mid + 1, m) > s) {
                R = m - 1;
                spl = m;
            } else {
                L = m + 1;
            }
        }
        ans += spl - (mid + 1);
    }
    mn = a[mid + 1], S = 0;
    for (int i = mid + 1; i <= r; i++) {
        mn = min(mn, a[i]);
        S += b[i];
        int L = l, R = mid, spl = l - 1;
        while (L <= R) {
            int m = (L + R) / 2;
            if (query(m, mid) <= mn || mn + S + query_s(m, mid) > s) {
                L = m + 1;
                spl = m;
            } else {
                R = m - 1;
            }
        }
        ans += mid - spl;
    }
    calc(l, mid, s);
    calc(mid + 1, r, s);
}

int main() {
    IOS;
    int n; ll s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + b[i];
    }
    build(n);
    calc(0, n - 1, s);
    cout << ans;
    return 0;
}
