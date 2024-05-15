//https://www.spoj.com/problems/DIVSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long M= 1e9 + 9;

long long dp[N][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int j = 1; j <= k; j++) {
        dp[1][j] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int p = j; p <= k; p += j) {
                dp[i][j] = (dp[i][j] + dp[i - 1][p]) % M;
                if (j != p) {
                    dp[i][p] = (dp[i][p] + dp[i - 1][j]) % M;
                }
            }
        }
    }
    long long ans = 0;
    for (int j = 1; j <= k; j++) {
        ans = (ans + dp[n][j]) % M;
    }
    cout << ans;

    return 0;
}
