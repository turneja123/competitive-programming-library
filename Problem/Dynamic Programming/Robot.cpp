//https://www.spoj.com/problems/ROOBOT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

const int N = 205;

ld dp[N][2 * N][2 * N];

int mnmx(int j, int i, int f) {
    if (f == 0) {
        return max(j, i);
    } else {
        return min(j, i);
    }
}

ld calc(int n, ld l, ld r, ld ud, int f) {
    dp[0][N][N] = 1.0;
    for (int k = 0; k < n; k++) {
        for (int i = 1; i < 2 * N - 1; i++) {
            for (int j = 1; j < 2 * N - 1; j++) {
                dp[k + 1][i - 1][mnmx(j, i - 1, f)] += dp[k][i][j] * l;
                dp[k + 1][i + 1][mnmx(j, i + 1, f)] += dp[k][i][j] * r;
                dp[k + 1][i][mnmx(j, i, f)] += dp[k][i][j] * ud;
            }
        }
    }
    ld ans = 0;
    for (int k = 0; k <= n; k++) {
        for (int i = 1; i < 2 * N - 1; i++) {
            for (int j = 1; j < 2 * N - 1; j++) {
                if (k == n) {
                    ans += dp[k][i][j] * (ld)(j - N);
                }
                dp[k][i][j] = 0;
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n;
    cin >> n;
    ld u, r, d, l;
    cin >> u >> r >> d >> l;
    ld ans = calc(n, l, r, u + d, 0) - calc(n, l, r, u + d, 1) + calc(n, d, u, l + r, 0) - calc(n, d, u, l + r, 1);
    cout << ans << endl;
    return 0;
}
