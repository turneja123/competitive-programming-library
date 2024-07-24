//https://www.spoj.com/problems/COLORSEG/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 51;
const int M = 1000003;

int dp[N][N][N][N]; //index, predzadnji, zadnji, najveca boja
int ans[N][N];

bool coprime[2 * N][2 * N];

int main() {
    IOS;
    for (int x = 1; x < N; x++) {
        for (int y = 1; y < N; y++) {
            dp[2][x][y][max(x, y)] = 1;
        }
    }
    for (int x = 1; x < 2 * N; x++) {
        for (int y = 1; y < 2 * N; y++) {
            if (__gcd(x, y) == 1) {
                coprime[x][y] = true;
            }
        }
    }
    int ct = 0;
    for (int i = 3; i < N; i++) {
        for (int m = 1; m < N; m++) {
            for (int x = 1; x <= m; x++) {
                for (int y = 1; y <= m; y++) {
                    for (int k = 1; k < N; k++) {
                        if (coprime[x + y][y + k]) {
                            dp[i][y][k][max(m, k)] = (dp[i][y][k][max(m, k)] + dp[i - 1][x][y][m]) % M;
                            ans[i][max(m, k)] = (ans[i][max(m, k)] + dp[i - 1][x][y][m]) % M;
                        }
                    }
                }
            }
        }

    }
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, m;
        cin >> n >> m;
        int sum = 0;
        if (n == 1) {
            sum = m;
        } else if (n == 2) {
            sum = m * m;
        } else {
            for (int j = 1; j <= m; j++) {
                sum += ans[n][j];
            }
        }
        cout << "Case " << tt << ": " << sum % M << endl;
    }
    return 0;
}
