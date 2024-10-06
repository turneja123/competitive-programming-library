//https://cses.fi/251/task/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

long long dp[2][N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    dp[0][1] = k > 1;
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[0][i] = (dp[0][i - 1] + dp[1][i - 1]) % M;
        if (i == k) {
            dp[0][i]--;
        } else if (i > k) {
            dp[0][i] = (dp[0][i] - dp[1][i - k] + M) % M;
        }
        if (k == 1) {
            dp[0][i] = 0;
        }
        dp[1][i] = (dp[0][i - 1] + dp[1][i - 1]) % M;
    }
    cout << (dp[0][n] + dp[1][n]) % M;

    return 0;

}
