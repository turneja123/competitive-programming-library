//https://www.codechef.com/START200A/problems/PERMCNTEZ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int N = 1e6 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (n == 2) {
            cout << 0 << endl;
            continue;
        }
        if (n == 3) {
            cout << 2 << endl;
            continue;
        }
        int f1 = (n + 2) / 3, f2 = (n + 1) / 3, f0 = n / 3;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + binomial(f1 + f2 + 2 - 2 * i, f0 - 2 * i + 1) * binomial(f1 - 1, i - 1) % M * binomial(f2 - 1, i - 1) % M * 2) % M;
            ans = (ans + binomial(f1 + f2 + 1 - 2 * i, f0 - 2 * i) * (binomial(f1 - 1, i - 1) * binomial(f2 - 1, i) % M + binomial(f1 - 1, i) * binomial(f2 - 1, i - 1) % M) % M) % M;
        }
        ans = ans * fact[f0] % M * fact[f1] % M * fact[f2] % M;
        cout << ans << endl;
    }
    return 0;
}
