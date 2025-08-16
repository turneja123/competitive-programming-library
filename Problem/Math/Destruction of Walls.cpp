//https://atcoder.jp/contests/arc203/tasks/arc203_c
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
    if (n < 0 || k < 0) {
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
        int n, m, k;
        cin >> n >> m >> k;
        int need = n + m - 2;
        if (k < need) {
            cout << 0 << endl;
            continue;
        }
        ll ans = binomial(n + m - 2, m - 1);
        ll tot = ((ll)(n - 1) * m + (ll)(m - 1) * n) % M;
        if (k == need + 1) {
            ans = ans * (tot - need + M) % M;
        }
        if (k == need + 2) {
            ans = ans * (tot - need + M) % M * (tot - need - 1 + M) % M * ((M + 1) / 2) % M;
            ans = (ans - binomial(n + m - 4, m - 2) % M * (n + m - 3) % M + M) % M;
            ans = (ans + binomial(n + m - 2, n - 3) * (m - 1)) % M;
            ans = (ans + binomial(n + m - 2, m - 3) * (n - 1)) % M;
        }
        cout << ans << endl;
    }
    return 0;
}
