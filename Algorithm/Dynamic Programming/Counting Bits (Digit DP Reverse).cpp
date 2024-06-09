//https://cses.fi/problemset/task/1146/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

long long dp[64][64][3];

long long calc(long long n) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 2);
        n /= 2;
    }
    reverse(b.begin(), b.end());
    long long ans = 1;
    dp[0][1][2] = 1;
    for (int i = 1; i < b.size(); i++) {
        int c = b[i];
        for (int j = 1; j < 64; j++) {
            if (c == 0) {
                //dodajem 0
                dp[i][j][2] += dp[i - 1][j][2];
                dp[i][j][1] += dp[i - 1][j][1];
                dp[i][j][0] += dp[i - 1][j][0];
                //dodajem 1
                dp[i][j][1] += dp[i - 1][j - 1][2] + dp[i - 1][j - 1][1];
                dp[i][j][0] += dp[i - 1][j - 1][0];

            } else {
                //dodajem 0
                dp[i][j][0] += dp[i - 1][j][2] + dp[i - 1][j][0];
                dp[i][j][1] += dp[i - 1][j][1];
                //dodajem 1
                dp[i][j][2] += dp[i - 1][j - 1][2];
                dp[i][j][1] += dp[i - 1][j - 1][1];
                dp[i][j][0] += dp[i - 1][j - 1][0];
            }
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (int j = 1; j < 64; j++) {
            ans += (dp[i][j][0] + dp[i][j][2]) * j;
            if (i != b.size() - 1) {
                ans += (dp[i][j][1]) * j;
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    long long n;
    cin >> n;
    cout << calc(n);
    return 0;
}
