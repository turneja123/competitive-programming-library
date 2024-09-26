//https://www.spoj.com/problems/VECTAR14/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long M = 1e9 + 7;

long long dp[N][N];
int last[2][N];

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        string a;
        cin >> a;
        dp[0][0] = 1;

        int n = a.size();
        for (int j = 0; j <= n; j++) {
            last[0][j] = -1;
            last[1][j] = -1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];
                if (a[i - 1] == '(' && j == 0) {
                    continue;
                }
                if (a[i - 1] == '(') {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % M;
                    if (last[0][j - 1] != -1) {
                        dp[i][j] = (dp[i][j] - dp[last[0][j - 1]][j - 1] + M) % M;
                    }
                    last[0][j - 1] = i - 1;
                } else {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % M;
                    if (last[1][j + 1] != -1) {
                        dp[i][j] = (dp[i][j] - dp[last[1][j + 1]][j + 1] + M) % M;
                    }
                    last[1][j + 1] = i - 1;
                }
            }
        }
        cout << dp[n][0] << endl;
	}

    return 0;
}
