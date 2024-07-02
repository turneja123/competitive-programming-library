//https://atcoder.jp/contests/abc360/tasks/abc360_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

long long dp[2][N];

long long modInverse(long long a) {
    a %= M;
    long long res = 1, y = M - 2;
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
    long long n, k;
    cin >> n >> k;
    dp[0][0] = 1, dp[1][0] = 0;
    long long tot = 1;
    for (int i = 1; i <= k; i++) {
        tot = tot * (n * n % M) % M;
        dp[1][i] = (2ll * (n - 1) * dp[0][i - 1] + (n * n % M) * dp[1][i - 1] - ((i == 1) ? 0 : 2ll * dp[1][i - 1] % M)) % M;
        dp[0][i] = (tot - dp[1][i] + M) % M;
    }
    long long ans = (dp[0][k] + (n + 2) * modInverse(2) % M * dp[1][k] % M) % M * modInverse(tot) % M;
    cout << ans;
    return 0;
}
