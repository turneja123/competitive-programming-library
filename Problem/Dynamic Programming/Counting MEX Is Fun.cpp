//https://www.codechef.com/START212A/problems/P6BAR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 1e9 + 7;

ll dp[N][N];
ll pw[N];

int main() {
    IOS;
    dp[0][0] = 1;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] * (i - 1)) % M;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (n == 1) {
            cout << (k == 1) << endl;
        } else {
            ll ans = (k < 3 ? 0 : dp[n - 1][k - 2] * pw[k - 2] % M);
            cout << ans << endl;
        }
    }


    return 0;
}
