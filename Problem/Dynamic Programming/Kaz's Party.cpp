//https://codeforces.com/gym/105698/problem/K
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

long double f[N];
long double d[N];

long double p[N][N];
long double dp[N];

long double ncr(int n, int k) {
    return f[n] / f[k] / f[n - k];
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    f[0] = 1.0;
    f[1] = 1.0;
    d[0] = 1.0;
    d[1] = 0.0;
    for (int i = 2; i < N; i++) {
        f[i] = f[i - 1] * (long double)i;
        d[i] = (d[i - 1] + d[i - 2]) * (long double)(i - 1);
    }
    for (int i = 1; i < N; i++) {
        p[i][0] = d[i] / f[i];
        for (int j = 1; j <= i; j++) {
            p[i][j] = ncr(i, j) * d[i - j] / f[i];
        }
    }
    dp[0] = 0.0;
    dp[1] = 0.0;
    for (int i = 2; i < N; i++) {
        for (int j = i; j > 0; j--) {
            dp[i] += p[i][j] * dp[i - j];
        }
        dp[i] = (dp[i] + 1.0) / (long double)(1.0 - p[i][0]);
    }
    int n;
    cin >> n;
    cout << dp[n] << endl;
    if (n == 1) {
        cout << 1;
    } else {
        for (int i = 2; i <= n; i++) {
            cout << i << " ";
        }
        cout << 1;
    }

    return 0;
}
