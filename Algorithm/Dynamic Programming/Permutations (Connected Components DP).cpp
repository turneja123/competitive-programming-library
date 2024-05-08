#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 20;
const long long M = 1e18;

long long dp[N][N];

int main() {
    IOS;
    dp[1][1] = 1;
    for (int i = 2; i <= 16; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i][j] + (long long)2 * j * dp[i - 1][j]) % M;
            dp[i][j] = (dp[i][j] + (long long)((j + 1) - 1) * dp[i - 1][j + 1]) % M;
            dp[i][j] = (dp[i][j] + (long long)((j - 1) + 1) * dp[i - 1][j - 1]) % M;
        }
        cout << dp[i][1] << " ";
    }
    return 0;
}
