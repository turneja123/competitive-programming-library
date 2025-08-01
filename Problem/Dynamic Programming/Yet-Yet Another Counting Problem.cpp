//https://www.spoj.com/problems/TREEII/
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

ll calc(int n, int m) {
    if (n - m < 0) {
        return 0;
    }
    if (n - m == 0) {
        return dp[n][m] = 1;
    }
    if (dp[n][m] != -1) {
        return dp[n][m];
    }
    ll ans = 0;
    for (int i = 1; i < N; i++) {
        if (n - m - m * i < 0) {
            break;
        }
        ans += calc(n - m, m * i);
    }
    return dp[n][m] = ans % M;
}

int main() {
    //IOS;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    calc(1000, 1);
    int n, t = 1;
    while (cin >> n) {
        cout << "Case " << t++ << ": " << dp[n][1] << endl;
    }
    return 0;
}
