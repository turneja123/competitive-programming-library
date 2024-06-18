//https://atcoder.jp/contests/abc358/tasks/abc358_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long M = 998244353;

int c[26];
int dp[26][N];

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
    long long num = fact[n];
    long long denom = (fact[k] * fact[n - k]) % M;
    return modDivide(num, denom);
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
    int n;
    cin >> n;
    for (int i = 0; i < 26; i++) {
        cin >> c[i];
    }
    for (int j = 0; j <= c[0]; j++) {
        dp[0][j] = 1;
    }
    for (int i = 1; i < 26; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= min(j, c[i]); k++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k] * binomial(j, k)) % M;
            }
        }
    }
    long long ans = 0;
    for (int j = 1; j <= n; j++) {
        ans = (ans + dp[25][j]) % M;
    }
    cout << ans;


    return 0;
}
