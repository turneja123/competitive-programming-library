//solution for https://www.e-olymp.com/en/problems/987
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

int a[N];
int dp[N][2];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    dp[1][1] = a[1] - a[0];
    dp[1][0] = a[1] - a[0];
    for (int i = 2; i < n; i++) {
        dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + a[i] - a[i - 1];
        dp[i][0] = dp[i - 1][1];
    }
    cout << dp[n - 1][1];



    return 0;
}
