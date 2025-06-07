//https://codeforces.com/contest/2115/problem/C
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define ld long double
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 25;
const int H = 405;
const int M = 4005;

int a[N];

long double pwp[M], pwip[M];
long double P[M];
long double dp[N][H][M];
bool seen[N][H][M];

ld binomial[M][M];

int n; ld prob;

ld calc(int i, int j, int k) {
    if (seen[i][j][k]) {
        return dp[i][j][k];
    }
    seen[i][j][k] = 1;
    if (j == 1 && i == 0) {
        return dp[i][j][k] = 1.0;
    }
    if (k == 0) {
        return dp[i][j][k] = 0.0;
    }
    dp[i][j][k] = prob * max(calc(i, max(1, j - 1), k - 1), calc(i, j, k - 1));
    if (i != 0) {
        dp[i][j][k] += ((ld)1.0 - prob) * calc(i - 1, j, k - 1);
    } else {
        dp[i][j][k] += ((ld)1.0 - prob) * max(calc(i, j, k - 1), calc(n - 1, j - 1, k - 1));
    }
    return dp[i][j][k];
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int t;
    cin >> t;
    binomial[0][0] = 1.0;
    for (int i = 1; i < M; i++) {
        binomial[i][0] = 1.0;
        binomial[i][i] = 1.0;
        for (int j = 1; j < i; j++) {
            binomial[i][j] = binomial[i - 1][j - 1] + binomial[i - 1][j];
        }
    }
    while (t--) {
        int m, p;
        cin >> n >> m >> p;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int h = a[0];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= h; j++) {
                for (int k = 0; k <= m; k++) {
                    seen[i][j][k]  = false;
                }
            }
        }
        prob = (ld)p / (ld)100;
        pwp[0] = 1.0, pwip[0] = 1.0;
        for (int i = 1; i <= m; i++) {
            pwp[i] = pwp[i - 1] * prob;
            pwip[i] = pwip[i - 1] * ((ld)1.0 - prob);
        }

        int s = 0;
        for (int i = 0; i < n; i++) {
            s += a[i] - h;
        }
        ld ans = 0.0;
        if (s > m) {
            cout << "0.0" << endl;
            continue;
        }
        if (s != 0) {
            for (int i = 0; i < s; i++) {
                P[i] = 0.0;
            }
            for (int i = s; i <= m; i++) {
                P[i] = binomial[i - 1][s - 1] * pwip[s] * pwp[i - s];
                ans += P[i] * calc(0, max(1, h - (i - s)), m - i);
            }
        } else {
            ans = calc(0, h, m);
        }
        cout << ans << endl;
    }
    return 0;
}
