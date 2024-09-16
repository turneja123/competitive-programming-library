//https://codeforces.com/contest/2005/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

vector<char> c{'n', 'a', 'r', 'e', 'k'};

const int N = 1e3 + 5;
const int INF = 1e9;

string s[N];
int dp[N][5];
bool narek[26];

int main() {
    IOS;
    for (char x : c) {
        narek[x - 'a'] = true;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
        }
        for (int k = 0; k < 5; k++) {
            dp[0][k] = -INF;
        }
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k < 5; k++) {
                dp[i][k] = dp[i - 1][k];
            }
            for (int k = 0; k < 5; k++) {
                if (dp[i - 1][k] == -INF) {
                    continue;
                }
                int sum = 0, ind = k;
                for (int j = 0; j < m; j++) {
                    if (s[i][j] == c[ind]) {
                        ind = (ind + 1) % 5;
                        sum++;
                    } else {
                        if (narek[s[i][j] - 'a']) {
                            sum--;
                        }
                    }
                }
                dp[i][ind] = max(dp[i][ind], dp[i - 1][k] + sum);
            }
        }
        int ans = 0;
        for (int k = 0; k < 5; k++) {
            ans = max(ans, dp[n][k] - 2 * k);
        }
        cout << ans << endl;


    }

    return 0;
}
