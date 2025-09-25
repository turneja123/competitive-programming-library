//https://basecamp.eolymp.com/en/problems/12215
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;


long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll calc(int n, int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        if (i > x / (y + 1)) {
            break;
        }
        if (i % 2 == 0) {
            ans = (ans + binomial(n, i) * binomial(x + n - 1 - i * (y + 1), n - 1)) % M;
        } else {
            ans = (ans - binomial(n, i) * binomial(x + n - 1 - i * (y + 1), n - 1) % M + M) % M;
        }
    }
    return ans;
}

ll f(int n, int x, int y) {
    return (calc(n, x, y) - calc(n, x - n, y - 1) + M) % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, x, k;
    cin >> n >> x >> k;
    ll ans = 0;
    for (int m = 1; m <= x; m++) {
        ans = (ans + binomial(n - 1, m - 1)) % M;
        for (int i = 1; i * m <= n; i++) {
            ans = (ans - f(m, n - i * m, k - 1) + M) % M;
        }
    }
    cout << ans;

    return 0;
}
