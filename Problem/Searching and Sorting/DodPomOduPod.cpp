//solution for http://algoge.com/problem/karantin_3_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

ll a[N];
vector<array<ll, 4>> queries(N);

ll calc(int pos, int q) {
    ll cur = a[pos];
    for (int i = 0; i < q; i++) {
        int Q = queries[i][0];
        ll x = queries[i][1];
        ll s = queries[i][2];
        ll t = queries[i][3];
        if (Q == 1) {
            if (cur >= x) {
                cur += s;
                cur *= t;
            }
        } else {
            if (cur <= x) {
                cur -= s;
                cur /= t;
            }
        }
    }
    return cur;
}

int findl(int n, int q, ll L) {
    int l = 0;
    int r = n - 1;
    int mn = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        ll after = calc(mid, q);
        if (after >= L) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return mn;
}

int findr(int n, int q, ll R) {
    int l = 0;
    int r = n - 1;
    int mx = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        ll after = calc(mid, q);
        if (after <= R) {
            mx = max(mx, mid);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return mx;
}

int main() {
    IOS;
    int n, q;
    ll l, r;
    cin >> n >> q >> l >> r;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> queries[i][j];
        }
    }
    sort(a, a + n);
    int L = findl(n, q, l);
    int R = findr(n, q, r);
    if (L == n || R == -1) {
        cout << 0;
    } else {
        cout << R - L + 1;
    }
    return 0;
}
