//https://www.spoj.com/problems/SPCO/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 66;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
long long dp[N][N][2];
bool prime[N];

long long calc(unsigned long long a) {
    if (a <= 1) {
        return 0;
    }
    int i = 0; long long ans = 0;
    while (a > 0) {
        int c = a & 1;
        for (int j = 0; j <= i + 1; j++) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
        }
        if (i == 0) {
            dp[i][0][0] = 1;
            if (c == 0) {
                dp[i][1][1] = 1;
            } else {
                dp[i][1][0] = 1;
            }
            a /= 2;
            i++;
            continue;
        }
        for (int j = 0; j < N; j++) {
            dp[i][j][0] += dp[i - 1][j][0];
            if (c == 0) {
                dp[i][j][1] += dp[i - 1][j][1];

                dp[i][j][1] += dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
                if (a > 1 && prime[j]) {
                    ans += dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1];
                }
            } else {
                dp[i][j][0] += dp[i - 1][j][1];
                dp[i][j][0] += dp[i - 1][j - 1][0];
                if (prime[j]) {
                    ans += dp[i - 1][j - 1][0];
                }
                dp[i][j][1] += dp[i - 1][j - 1][1];
                if (a > 1 && prime[j]) {
                    ans += dp[i - 1][j - 1][1];
                }
            }
        }
        a >>= 1;
        i++;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    for (int i = 0; i < primes.size(); i++) {
        prime[primes[i]] = true;
    }
    while (t--) {
        unsigned long long a, b;
        cin >> a >> b;
        long long ans = calc(b) - calc(a - 1);
        cout << ans << endl;

    }

    return 0;
}
