//solution for https://www.e-olymp.com/en/problems/1619
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

ll a[N];
ll dp[N][2];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[0][0] = 0;
    dp[0][1] = a[0];
    dp[1][0] = a[0];
    dp[1][1] = a[1];
    for (int i = 2; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = max(dp[i - 1][0], max(dp[i - 2][0], dp[i - 2][1])) + a[i];
    }
    cout << max(dp[n - 1][0], dp[n - 1][1]);

    return 0;
}
