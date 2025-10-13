//https://codeforces.com/contest/2145/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10;
const int M = 2520;
const int K = 60;

int a[N], b[N];
bool can[N][M];

ll dp[K][M][N];

ll calc(int i, int m, int j, int n) {
    if (dp[i][m][j] != -1) {
        return dp[i][m][j];
    }
    if (i == 0) {
        return dp[i][m][j] = can[j][m];
    }

    ll d = calc(i - 1, m, j, n);
    int m_nx = (m + d) % M;
    return dp[i][m][j] = d + calc(i - 1, (m + d) % M, (j + (1ll << i - 1)) % n, n);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; ll need;
        cin >> n >> need;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < M; j++) {
                if ((j + 1) % a[i] != b[i]) {
                    can[i][j] = 1;
                } else {
                    can[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < K; i++) {
            for (int m = 0; m < M; m++) {
                for (int j = 0; j < n; j++) {
                    dp[i][m][j] = -1;
                }
            }
        }
        calc(K - 1, 0, 0, n);
        if (dp[K - 1][0][0] < need) {
            cout << -1 << endl;
        } else {
            ll ans = 0;
            int m = 0, j = 0;
            for (int i = K - 1; i >= 0; i--) {
                if (need > dp[i][m][j]) {
                    ans += 1ll << i;
                    need -= dp[i][m][j];
                    m = (m + dp[i][m][j]) % M;
                    j = (j + (1ll << i)) % n;
                }
            }
            cout << ans + 1 << endl;
        }

    }
    return 0;
}
