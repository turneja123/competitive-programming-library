//https://www.spoj.com/problems/VZLA2019E/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N][2];
int dp[N][2];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i][0];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i][1];
    }
    dp[0][0] = a[0][1], dp[0][1] = a[0][0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0], dp[i][1] = dp[i - 1][1];
        dp[i][0] = max(dp[i][0], dp[i - 1][1] + a[i][1]);
        dp[i][1] = max(dp[i][1], dp[i - 1][0] + a[i][0]);
    }
    cout << max(dp[n - 1][0], dp[n - 1][1]);

    return 0;
}
