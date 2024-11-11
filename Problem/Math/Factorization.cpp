//https://atcoder.jp/contests/abc110/tasks/abc110_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 3e5 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

long long stars(long long n, long long k) {
    return binomial(n + k - 1, n);
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, m;
    cin >> n >> m;
    long long ans = 1;
    for (int i = 2; i <= sqrt(m); i++) {
        int e = 0;
        while (m % i == 0) {
            e++;
            m /= i;
        }
        if (e > 0) {
            ans = ans * stars(e, n) % M;
        }
    }
    if (m > 1) {
        ans = ans * n % M;
    }
    cout << ans;

    return 0;
}
