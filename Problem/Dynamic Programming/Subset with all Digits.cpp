//https://www.spoj.com/problems/THECODE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 10;

int flag[1 << K];
int dp[1 << K];
bool can = false;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        for (int mask = 1; mask < (1 << K); mask++) {
            flag[mask] = 0;
            dp[mask] = K + 1;
        }
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            int mask = 0;
            for (int i = 0; i < m; i++) {
                int j = s[i] - '0';
                mask |= 1 << j;
            }
            flag[mask] = 1;
        }
        for (int mask = (1 << K) - 1; mask > 0; mask--) {
            if (flag[mask] == 1) {
                for (int j = mask; j > 0; j = (j - 1) & mask) {
                    dp[j] = 1;
                }
            }
        }
        for (int j = 2; j <= 10; j++) {
            for (int mask = 1; mask < (1 << K); mask++) {
                if (dp[mask] < j) {
                    continue;
                }
                for (int j = mask; j > 0; j = (j - 1) & mask) {
                    if (j == mask) {
                        continue;
                    }
                    dp[mask] = min(dp[mask], dp[j] + dp[mask ^ j]);
                }
            }
            if (dp[(1 << K) - 1] != K + 1) {
                break;
            }
        }
        if (dp[(1 << K) - 1] == K + 1) {
            cout << -1 << endl;
        } else {
            cout << dp[(1 << K) - 1] << endl;
        }
    }
    return 0;
}
