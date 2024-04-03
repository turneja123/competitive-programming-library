//https://dmoj.ca/problem/bts18p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const long long M = 998244353;

long long dp[N][N];
long long a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[0][0] = 1;
    dp[0][1] = (a[0] % M + M) % M;
    for (int i = 1; i < n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= n; j++) {
            dp[i][j] = ((dp[i - 1][j] + dp[i - 1][j - 1] * a[i]) % M + M) % M;
        }
    }
    for (int j = 1; j <= n; j++) {
        cout << dp[n - 1][j] << " ";
    }
    return 0;
}
