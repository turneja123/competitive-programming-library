//solution for https://cses.fi/problemset/task/2086/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

long long a[N];
long long pref[N];
long long dp[N][N];

long long sq(long long val) {
    return val * val;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = a[i];
        if (i != 0) {
            pref[i] += pref[i - 1];
        }
    }
    for (int j = 0; j < n; j++) {
        dp[1][j] = pref[j] * pref[j];
    }
    for (int i = 2; i <= n; i++) {
        int l = i - 2;
        for (int j = i - 1; j < n; j++) {
            dp[i][j] = dp[i - 1][l] + sq(pref[j] - pref[l]);
            for (int p = l + 1; p < j; p++) {
                if (dp[i - 1][p] + sq(pref[j] - pref[p]) <= dp[i][j]) {
                    dp[i][j] = dp[i - 1][p] + sq(pref[j] - pref[p]);
                    l = p;
                }

            }
        }
    }
    cout << dp[k][n - 1] << endl;
    return 0;
}
