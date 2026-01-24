//https://codeforces.com/contest/2190/problem/B2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const ll M = 998244353;


pair<ll, ll> dp[N][N][2][2][2]; // suma, zadnji, ima )(, ima ( posle )(

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i + 1; j++) {
                for (int last = 0; last < 2; last++) {
                    for (int x = 0; x < 2; x++) {
                        for (int y = 0; y < 2; y++) {
                            dp[i][j][last][x][y] = {0, 0};
                        }
                    }
                }
            }
        }
        if (s[0] == '(') {
            dp[0][1][1][0][0] = {1, 1};
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                for (int last = 0; last < 2; last++) {
                    for (int x = 0; x < 2; x++) {
                        for (int y = 0; y < 2; y++) {
                            dp[i][j][last][x][y].first = (dp[i][j][last][x][y].first + dp[i - 1][j][last][x][y].first) % M;
                            dp[i][j][last][x][y].second = (dp[i][j][last][x][y].second + dp[i - 1][j][last][x][y].second) % M;
                        }
                    }
                }
            }


            int d = (s[i] == '(' ? 1 : 0);
            for (int j = 0; j <= i; j++) {
                int nx_j = j + (d == 1 ? 1 : -1);
                if (nx_j < 0) {
                    continue;
                }
                for (int last = 0; last < 2; last++) {
                    for (int x = 0; x < 2; x++) {
                        for (int y = 0; y < 2; y++) {
                            int nx_last = (d == 1 ? 1 : 0);
                            int nx_x = (x || (last == 0 && d == 1));
                            int nx_y = (y || (x && d == 1));
                            dp[i][nx_j][nx_last][nx_x][nx_y].first = (dp[i][nx_j][nx_last][nx_x][nx_y].first + dp[i - 1][j][last][x][y].first) % M;
                            dp[i][nx_j][nx_last][nx_x][nx_y].second = (dp[i][nx_j][nx_last][nx_x][nx_y].second + dp[i - 1][j][last][x][y].second + dp[i - 1][j][last][x][y].first) % M;
                        }
                    }
                }
            }
            if (d == 1) {
                dp[i][1][1][0][0].first = (dp[i][1][1][0][0].first + 1) % M;
                dp[i][1][1][0][0].second = (dp[i][1][1][0][0].second + 1) % M;
            }
        }
        ll ans = 0;
        for (int last = 0; last < 2; last++) {
            ans = (ans + dp[n - 1][0][last][1][1].second - dp[n - 1][0][last][1][1].first * 2 % M + M) % M;
        }
        cout << ans << endl;

    }
    return 0;
}
