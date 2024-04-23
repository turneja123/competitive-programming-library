//https://www.spoj.com/problems/ADV04B1/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1000003;

long long dp[N];

long long modInverse(long long a, long long m) {
    long long res = 1;
    long long y = m - 2;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

long long modDivide(long long a, long long b, long long m) {
    long long inv = modInverse(b, m);
    return (inv * a) % m;
}

int main() {
    IOS;
    dp[0] = 1, dp[1] = 3;
    for (long long i = 2; i < N; i++) {
        dp[i] = modDivide((3 * (2 * i - 1) * dp[i - 1] % M - (i - 1) * dp[i - 2] % M + M) % M, i, M);
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << dp[n - 1] << endl;
    }

    return 0;
}
