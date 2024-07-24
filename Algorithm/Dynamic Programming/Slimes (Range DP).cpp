//https://atcoder.jp/contests/dp/tasks/dp_n
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const long long INF = 1e18;

long long a[N];
long long dp[N][N];
long long pref[N];

long long sum(int l, int r) {
    return pref[r] - ((l == 0) ? 0 : pref[l - 1]);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = 0;
                continue;
            }
            dp[j][j + i] = INF;
            for (int k = j; k < j + i; k++) {
                dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i] + sum(j, j + i));
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
