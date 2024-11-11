//https://codeforces.com/problemset/problem/1288/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 3e5 + 5;

long long a[N], b[N];
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
    for (int i = 1; i <= n; i++) {
        a[i]++;
        b[i]++;
        if (m == 1) {
            continue;
        }
        for (int j = 1; j + i <= n; j++) {
            a[i + j] = (a[i + j] + stars(j, m - 1)) % M;
        }
        for (int j = 1; j < i; j++) {
            b[i - j] = (b[i - j] + stars(j, m - 1)) % M;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            ans += a[j] * b[i] % M;
        }
    }
    cout << ans % M;
    return 0;
}
