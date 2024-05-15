//https://www.spoj.com/problems/DRACULA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 20;

long long dp[N][10 * N][2];
long long ct[10 * N];

void calc(long long a, long long sgn) {
    for (int i = 0; i < 10; i++) {
        dp[0][i][0] = 0;
        dp[0][i][1] = 0;
        if (a % 10 >= i) {
            dp[0][i][0] = 1;
        } else {
            dp[0][i][1] = 1;
        }
        if (a >= i) {
            ct[i] += sgn;
        }
    }
    a /= 10;
    for (int i = 1; a > 0; a /= 10, i++) {
        for (int j = 0; j < 10 * (i + 1); j++) {
            dp[i][j][0] = 0;
            dp[i][j][1] = 0;
            for (int d = 0; d < 10; d++) {
                if (j < d) {
                    continue;
                }
                if (a % 10 > d) {
                    dp[i][j][0] += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                    if (d != 0) {
                        ct[j] += (dp[i - 1][j - d][0] + dp[i - 1][j - d][1]) * sgn;
                    }
                } else if (a % 10 == d) {
                    dp[i][j][0] += dp[i - 1][j - d][0];
                    dp[i][j][1] += dp[i - 1][j - d][1];
                    if (d != 0) {
                        ct[j] += dp[i - 1][j - d][0]  * sgn;
                        if (a > 9) {
                            ct[j] += dp[i - 1][j - d][1] * sgn;
                        }
                    }
                } else {
                    dp[i][j][1] += dp[i - 1][j - d][0] + dp[i - 1][j - d][1];
                    if (d != 0 && a > 9) {
                        ct[j] += (dp[i - 1][j - d][0] + dp[i - 1][j - d][1]) * sgn;
                    }
                }
            }
        }
    }
    return;
}

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        long long a, b, x;
        cin >> a >> b >> x;
        calc(b, 1);
        calc(a - 1, -1);
        long long ans = 0;
        for (int i = 1; i < 10 * N && x >= i; i++) {
            if (x >= ct[i] * i) {
                ans += ct[i];
                x -= ct[i] * i;
            } else {
                ans += x / i;
                x %= i;
            }
        }
        for (int i = 1; i < 10 * N; i++) {
            ct[i] = 0;
        }
        cout << ans << endl;
	}

	return 0;
}
