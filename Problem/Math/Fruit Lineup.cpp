//https://atcoder.jp/contests/abc405/tasks/abc405_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e6 + 5;
const long long M = 998244353;

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
    int a, o, b, g;
    cin >> a >> o >> b >> g;
    long long ans = 0;
    int n = a + o + b + g;
    for (int i = a; i <= n; i++) {
        if (n - i < b + g) {
            break;
        }
        ans = (ans + binomial(i - 1, a - 1) * binomial(n - i, b)) % M;
    }
    cout << ans;
    return 0;
}

