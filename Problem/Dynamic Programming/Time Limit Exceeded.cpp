//https://www.spoj.com/problems/TLE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 55;
const int K = 15;
const long long M = 1e9;

long long a[N];
long long dp[N][1 << K];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int bits = 1 << m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int j = 1; j < bits; j++) {
            dp[0][j] = 0;
            if (j % a[0] == 0) {
                continue;
            }
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < bits; j++) {
                dp[i][j] = dp[i - 1][j];
            }
            for (int k = 0; k < m; k++) {
                for (int j = 0; j < bits; j++) {
                    if (j & (1 << k)) {
                        dp[i][j] += dp[i][j ^ (1 << k)];
                        dp[i][j] %= M;
                    }
                }
            }
            vector<long long> temp(bits, 0);
            for (int j = 1; j < bits; j++) {
                temp[j] = dp[i][j];
            }
            for (int j = 0; j < bits; j++) {
                int complement = (bits - 1) ^ j;
                dp[i][j] = temp[complement];
                if (j % a[i] == 0) {
                    dp[i][j] = 0;
                }
            }
        }
        long long ans = 0;
        for (int j = 1; j < bits; j++) {
            ans += dp[n - 1][j];
        }
        cout << ans % M << endl;
    }

    return 0;
}
