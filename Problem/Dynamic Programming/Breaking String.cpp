//https://www.spoj.com/problems/BRKSTRNG/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long INF = 1e18;

long long a[N];
long long dp[N][N];
int opt[N][N];

int main() {
    IOS;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        int n, m;
        iss >> m >> n;
        getline(cin, line);
        istringstream is(line);
        a[0] = 0;
        for (int i = 1; i <= n; i++) {
            is >> a[i];
        }
        a[n + 1] = m;
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j + i <= n + 1; j++) {
                if (i < 2) {
                    opt[j][j + i] = j;
                    dp[j][j] = 0;
                    continue;
                }
                if (i == 2) {
                    opt[j][j + i] = j + 1;
                    dp[j][j + i] = a[j + i] - a[j];
                    continue;
                }
                dp[j][j + i] = INF;

                for (int k = max(j, opt[j][j + i - 1]); k <= min(j + i, opt[j + 1][j + i]); k++) {
                    long long cost = dp[j][k] + dp[k][j + i] + a[j + i] - a[j];
                    if (cost < dp[j][j + i]) {
                        dp[j][j + i] = cost;
                        opt[j][j + i] = k;
                    }
                }
            }
        }
        cout << dp[0][n + 1] << endl;
    }
    return 0;
}
