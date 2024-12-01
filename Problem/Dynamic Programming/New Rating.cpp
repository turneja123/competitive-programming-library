//https://codeforces.com/contest/2029/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int dp[N][3];
int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        dp[0][0] = 1, dp[0][1] = 0, dp[0][2] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0];
            if (a[i] < dp[i][0]) {
                dp[i][0]--;
            } else if (a[i] > dp[i][0]) {
                dp[i][0]++;
            }
            dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][2] = max(dp[i - 1][1], dp[i - 1][2]);
            if (a[i] < dp[i][2]) {
                dp[i][2]--;
            } else if (a[i] > dp[i][2]) {
                dp[i][2]++;
            }
        }
        cout << max({dp[n - 1][1], dp[n - 1][2]}) << endl;
    }

    return 0;
}
