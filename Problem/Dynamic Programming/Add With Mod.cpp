//https://www.codechef.com/START222A/problems/ADDMOD
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 50;
ll M;

ll inv[N];
ll fact[N];
ll factinv[N];
ll dp[N][N][N][N];
ll dpa[N][N][N];


int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n >> M;
        fact[0] = 1, factinv[0] = 1;
        for (int i = 1; i < N; i++) {
            inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
            fact[i] = fact[i - 1] * i % M;
            factinv[i] = factinv[i - 1] * inv[i] % M;
        }
        for (int i = 1; i <= n; i++) {
            for (int ja = 0; ja <= n; ja++) {
                for (int jb = 0; jb <= n; jb++) {
                    for (int k = 0; k <= n; k++) {
                        dp[i][ja][jb][k] = 0;
                    }
                }
            }
        }
        dp[0][0][0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int ja = 0; ja <= n; ja++) {
                for (int jb = 0; jb <= n; jb++) {
                    for (int k = 0; k <= n; k++) {
                        dpa[ja][jb][k] = 0;
                    }
                }
            }
            for (int ja = 0; ja <= n; ja++) {
                for (int jb = 0; jb <= n; jb++) {
                    for (int adda = 0; adda + ja <= n; adda++) {
                        for (int k = 0; k <= n; k++) {
                            dpa[ja + adda][jb][k] = (dpa[ja + adda][jb][k] + dp[i - 1][ja][jb][k] * factinv[adda]) % M;
                        }
                    }
                }
            }
            for (int ja = 0; ja <= n; ja++) {
                for (int jb = 0; jb <= n; jb++) {
                    for (int addb = 0; addb + jb <= n; addb++) {
                        int dist = addb + jb - ja;
                        for (int k = 0; k <= n; k++) {
                            dp[i][ja][jb + addb][max(k, dist)] = (dp[i][ja][jb + addb][max(k, dist)] + dpa[ja][jb][k] * factinv[addb]) % M;
                        }
                    }
                }
            }
        }
        ll ans = 0;
        for (int k = 1; k <= n; k++) {
            ans = (ans + dp[n][n][n][k] * k % M * fact[n] % M * fact[n] % M * n % M) % M;
        }
        cout << ans << endl;

    }


    return 0;
}
