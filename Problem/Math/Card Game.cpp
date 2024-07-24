//https://codeforces.com/contest/1739/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 998244353;
const int N = 100;

long long ans = 0;
long long fact[N];

long long modInverse(long long a) {
    long long res = 1;
    long long y = M - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

long long modDivide(long long a, long long b) {
    a = a % M;
    long long inv = modInverse(b);
    return (inv * a) % M;
}

long long binomial(long long n, long long k) {
    if (k < 0) {
        return 0;
    }
    long long num = fact[n];
    long long denom = (fact[k] * fact[n - k]) % M;
    return modDivide(num, denom);
}

void calc(int n, int flag) {
    if (n < 0) {
        return;
    }
    if (flag == 0) {
        ans = (ans + binomial(n - 1, n / 2 - 1)) % M;
    } else {
        ans = (ans + binomial(n - 2, n / 2 - 2)) % M;
    }
    calc(n - 2, flag ^ 1);
}

int main() {
    IOS;
    long long f = 1;
    fact[0] = 1;
    for (long long i = 1; i < N; i++) {
        f *= i;
        f %= M;
        fact[i] = f;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ans = 0;
        calc(n, 0);
        cout << ans << " " << (binomial(n, n / 2) - ans - 1 + M) % M << " " << 1 << endl;
    }

    return 0;
}
