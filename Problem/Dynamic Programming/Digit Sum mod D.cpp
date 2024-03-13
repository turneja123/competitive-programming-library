//https://atcoder.jp/contests/dp/tasks/dp_s
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10005;
const int D = 105;
const long long M = 1e9 + 7;

long long dp[N][D][2];

int main() {
    IOS;
    string s;
    cin >> s;
    int d, n = s.size();
    cin >> d;
    long long ans = 0;
    for (int i = 0; i <= 9; i++) {
        int c = s[n - 1] - '0';
        if (i <= c) {
            dp[n - 1][i % d][0]++;
            if (i % d == 0) {
                ans++;
            }
        } else {
            dp[n - 1][i % d][1]++;
            if (s.size() > 1 && i % d == 0) {
                ans++;
            }
        }
    }
    ans--;
    for (int i = n - 2; i >= 0; i--) {
        int c = s[i] - '0';
        for (int m = 0; m < d; m++) {
            for (int cif = 0; cif <= 9; cif++) {
                if (cif < c) {
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                    if (m == 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                        ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                    }
                } else if (cif > c) {
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                    if (m == 0 && i > 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                        ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                    }
                } else {
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                    if (m == 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][0]) % M;
                        if (i > 0) {
                            ans = (ans + dp[i + 1][(m - cif + 9 * d) % d][1]) % M;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;

    return 0;
}
