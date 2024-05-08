//https://www.spoj.com/problems/PLOVER/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 40;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
long long dp[N][2 * N][2];
bool is_prime[N];

long long calc(long long n) {
    long long ans = n >= 2;
    for (int j = 0; j <= 2; j++) {
        if (j <= n % 3) {
            dp[0][j][0] = 1;
        } else {
            dp[0][j][1] = 1;
        }
    }
    int i = 1; n /= 3;
    while (n > 0) {
        for (int j = 0; j <= (i + 1) * 2; j++) {
            for (int d = 0; d <= 2; d++) {
                if (j < d) {
                    continue;
                }
                if (d < n % 3) {
                    dp[i][j][0] += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                    if (d != 0 && is_prime[j]) {
                        ans += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                    }
                } else if (d == n % 3) {
                    dp[i][j][0] += dp[i - 1][j - d][0];
                    dp[i][j][1] += dp[i - 1][j - d][1];
                    if (d != 0 && is_prime[j]) {
                        ans += dp[i - 1][j - d][0];
                        if (n >= 3) {
                            ans += dp[i - 1][j - d][1];
                        }
                    }
                } else {
                    dp[i][j][1] += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                    if (d != 0 && is_prime[j]) {
                        if (n >= 3) {
                            ans += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                        }
                    }
                }
            }
        }
        n /= 3;
        i++;
    }
    for (int ii = 0; ii < i; ii++) {
        for (int j = 0; j <= (ii + 1) * 2; j++) {
            dp[ii][j][0] = 0;
            dp[ii][j][1] = 0;
        }
    }
    return ans;
}

int main() {
    IOS;
    for (int p : primes) {
        is_prime[p] = true;
    }
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        long long l = 1, r = n, ans = n + 1;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long ct = calc(mid);
            if (ct >= k) {
                if (ct == k) {
                    ans = min(ans, mid);
                }
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (ans > n) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }

    return 0;
}
