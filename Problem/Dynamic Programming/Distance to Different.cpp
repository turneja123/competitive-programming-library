//https://codeforces.com/contest/1989/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int N = 2e5 + 5;
const int K = 11;

long long dp[N][K][3];
long long all[N][3];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    dp[1][1][0] = 1;
    all[1][0] = 1;
    for (int i = 2; i < N; i++) {
        all[i][0] = (all[i][0] + all[i - 1][0] + all[i - 1][2] + (i == 3 ? all[i - 1][1] : 0)) % M;
        all[i][1] = (all[i][1] + all[i - 1][0]) % M;
        all[i][2] = (all[i][2] + all[i - 1][1] + all[i - 1][2]) % M;
        for (int j = 1; j < K; j++) {
            dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][0] + dp[i - 1][j - 1][2] + (i == 3 ? dp[i - 1][j - 1][1] : 0)) % M;
            dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j][0]) % M;
            dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j][1] + dp[i - 1][j][2]) % M;
        }
    }
    long long ans = (all[n][0] + all[n][1] + all[n][2]) % M;
    for (int j = 1; j < k; j++) {
        ans = (ans - dp[n][j][0] - dp[n][j][1] - dp[n][j][2] + 3 * M) % M;
    }
    cout <<  ans;
    return 0;
}
