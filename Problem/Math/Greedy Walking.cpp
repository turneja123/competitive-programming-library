//https://www.spoj.com/problems/UCV2013E/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 1e5 + 5;

int a[N];
long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
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
    int n;
    cin >> n;
    while (n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int m = 0;
        for (int i = 0; i < n; i++) {
            int b;
            cin >> b;
            a[i] = b - a[i];
            m += a[i];
        }
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            ans = ans * binomial(m, a[i]) % M;
            m -= a[i];
        }
        cout << ans << endl;
        cin >> n;
    }
    return 0;
}
