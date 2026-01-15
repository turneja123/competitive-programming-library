//https://dmoj.ca/problem/aaaa1p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;
const ll M = 1e9 + 7;

int a[N][N];
int need[N * N];
pair<int, int> pos[N * N];
ll dp[N][N];
ll dp_nx[N][N];
ll dp_xy[N][N];
ll dp_x[N][N];
ll dp_y[N][N];

ll inv[N * N];
ll fact[N * N];
ll factinv[N * N];

ll binomial(ll n, ll k) {
    if (k > n) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N * N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            pos[a[i][j]] = {i, j};
        }
    }
    auto [x, y] = pos[0];
    int lx = x, rx = x, ly = y, ry = y;
    need[0] = 1;
    for (int i = 1; i < n * m; i++) {
        auto [x, y] = pos[i];
        int n_lx = min(lx, x), n_rx = max(rx, x);
        int n_ly = min(ly, y), n_ry = max(ry, y);

        if (n_lx != lx || n_ly != ly || n_rx != rx || n_ry != ry) {
            need[i] = 1;
            lx = n_lx;
            ly = n_ly;
            rx = n_rx;
            ry = n_ry;
        }
    }
    dp[1][1] = 1;
    for (int i = 1; i < n * m;) {
        int mul = 0, st = i;
        while (i < n * m && !need[i]) {
            i++;
            mul++;
        }
        if (mul) {
            for (int x = 1; x <= n; x++) {
                for (int y = 1; y <= m; y++) {
                    dp[x][y] = dp[x][y] * binomial(x * y - st, mul) % M * fact[mul] % M;
                }
            }
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                dp_xy[x][y] = (dp_xy[x - 1][y] + dp_xy[x][y - 1] - dp_xy[x - 1][y - 1] + dp[x][y] + M) % M;
                dp_x[x][y] = (dp_x[x][y - 1] + dp[x][y]) % M;
            }
        }
        for (int y = 1; y <= m; y++) {
            for (int x = 1; x <= n; x++) {
                dp_y[x][y] = (dp_y[x - 1][y] + dp[x][y]) % M;
            }
        }


        if (i == n * m) {
            break;
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                dp_nx[x][y] = (dp_nx[x][y] + dp_xy[x - 1][y - 1] * 4) % M;
                dp_nx[x][y] = (dp_nx[x][y] + dp_x[x][y - 1] * 2 * x) % M;
                dp_nx[x][y] = (dp_nx[x][y] + dp_y[x - 1][y] * 2 * y) % M;
            }
        }
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                dp[x][y] = dp_nx[x][y];
                dp_nx[x][y] = 0;
            }
        }
        i++;
    }
    cout << dp[n][m];
    return 0;
}
