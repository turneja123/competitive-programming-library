//https://atcoder.jp/contests/abc333/tasks/abc333_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const long long M = 998244353;

long long ans[N][N];
long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
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
    ans[1][1] = 1;
    for (int i = 2; i < N; i++) {
        long long sum = 0;
        for (int j = 1; j < i; j++) {
            sum = (sum + ans[j][1] * binomial(i - 1, j - 1) % M) % M;
        }
        sum = sum * 2 % M * modPow(modPow(2, i) - 1, M - 2) % M;
        ans[i][i] = sum;
        ans[i][1] = sum * modPow(2, M - 2) % M;
    }
    for (int i = 2; i < n; i++) {
        for (int j = n - i + 1, k = 0; j <= n; j++, k++) {
            ans[n][i] = (ans[n][i] + ans[j][1] * binomial(i - 1, k) % M) % M;
        }
        ans[n][i] = ans[n][i] * modPow(modPow(2, i - 1), M - 2) % M;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[n][i] << " ";
    }

    return 0;
}
