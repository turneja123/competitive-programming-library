//https://www.spoj.com/problems/COWWORDS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long M = 97654321;

vector<pair<int, int>> can;

long long dp[N][N][52];

int main() {
    IOS;
    int x, y, m;
    cin >> x >> y >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        int a = ((isupper(s[0]) ? 26 + (s[0] - 'A') : s[0] - 'a')),
            b = ((isupper(s[1]) ? 26 + (s[1] - 'A') : s[1] - 'a'));
        can.push_back(make_pair(a, b));
    }
    int n = x + y;
    for (int i = 0; i < 26; i++) {
        dp[0][0][i] = 1;
    }
    for (int i = 26; i < 52; i++) {
        dp[0][1][i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                int a = can[k].first, b = can[k].second;
                if (j == 0 && b >= 26) {
                    continue;
                }
                dp[i][j][b] = (dp[i][j][b] + dp[i - 1][j - (b >= 26)][a]) % M;
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < 52; i++) {
        ans = (ans + dp[n - 1][x][i]) % M;
    }
    cout << ans;
    return 0;
}
