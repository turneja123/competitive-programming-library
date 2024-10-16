//https://www.spoj.com/problems/DABRI001/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e6 + 5;

int a[N];
int dp[2][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]++;
    }
    dp[0][a[0]] = 1, dp[1][a[0]] = 2;
    int ans = 2;
    for (int i = 1; i < n; i++) {
        dp[0][a[i]] = dp[0][a[i] - 1] + 1;
        dp[1][a[i]] = dp[1][a[i] - 1] + 1;
        dp[1][a[i] + 1] = max(dp[1][a[i] + 1], dp[0][a[i]] + 1);
        ans = max({ans, dp[1][a[i]], dp[1][a[i] + 1]});
    }
    cout << ans;


    return 0;
}
