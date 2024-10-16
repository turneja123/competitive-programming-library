//https://cses.fi/problemset/task/1079/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 1e6 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, fact[1] = 1;
    factinv[0] = 1, factinv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < N; i++) {
        inv[i] = M - (M / i) * inv[M % i] % M;
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long n, k;
        cin >> n >> k;
        cout << binomial(n, k) << endl;
    }
    return 0;
}
