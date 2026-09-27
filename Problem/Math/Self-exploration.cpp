//https://codeforces.com/contest/1045/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll stars(ll n, ll k) {
    if (n < 0 || k < 0) {
        return 0;
    }
    if (k == 0) {
        return n == 0;
    }
    return binomial(n + k - 1, k - 1);
}

ll calc(int l, int n, int c00, int c01, int c10, int c11) {
    if (c00 < 0 || c01 < 0 || c10 < 0 || c11 < 0) {
        return 0;
    }
    if (n == 0) {
        return (c00 + c01 + c10 + c11) == 0;
    }

    int b0, b1;
    if (l == 1) {
        if (c10 == c01 + 1) {
            b0 = c10;
            b1 = c10;
        } else if (c10 == c01) {
            b0 = c10;
            b1 = c10 + 1;
        } else {
            return 0;
        }
    }
    if (l == 0) {
        if (c10 == c01 - 1) {
            b0 = c01;
            b1 = c01;
        } else if (c10 == c01) {
            b0 = c01 + 1;
            b1 = c01;
        } else {
            return 0;
        }
    }
    ll ans = stars(c00, b0) * stars(c11, b1) % M;
    return ans;
}

ll solve(string a, int c00, int c01, int c10, int c11, int f) {
    int n = a.size();
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] == '1') {
            ans = (ans + calc(0, n - i - 1, c00 - (a[i - 1] == '0'), c01, c10 - (a[i - 1] == '1'), c11)) % M;
        }
        if (a[i - 1] == '0' && a[i] == '0') {
            c00--;
        } else if (a[i - 1] == '0' && a[i] == '1') {
            c01--;
        } else if (a[i - 1] == '1' && a[i] == '0') {
            c10--;
        } else if (a[i - 1] == '1' && a[i] == '1') {
            c11--;
        }
    }
    if (f) {
        ans = (ans + (c00 == 0 && c01 == 0 && c10 == 0 && c11 == 0)) % M;
    }
    return ans;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    string a, b;
    cin >> a >> b;
    int c00, c01, c10, c11;
    cin >> c00 >> c01 >> c10 >> c11;
    int d = c00 + c01 + c10 + c11 + 1;
    if (a.size() < d && d < b.size()) {
        cout << calc(1, d - 1, c00, c01, c10, c11) << endl;
    } else if (a.size() == d && d < b.size()) {
        cout << (calc(1, d - 1, c00, c01, c10, c11) - solve(a, c00, c01, c10, c11, 0) + M) %M << endl;
    } else if (a.size() < d && d == b.size()) {
        cout << solve(b, c00, c01, c10, c11, 1) << endl;
    } else if (a.size() == d && d == b.size()) {
        ll ans = (solve(b, c00, c01, c10, c11, 1) - solve(a, c00, c01, c10, c11, 0) + M) % M;
        cout << ans << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
