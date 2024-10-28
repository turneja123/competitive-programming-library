//https://codeforces.com/contest/2033/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

int a[N];
int dp[N][2];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i][0] = 0;
            dp[i][1] = 0;
        }
        for (int i = 1; i < n / 2; i++) {
            dp[i][0] += min(dp[i - 1][0] + (a[i] == a[i - 1]) + (a[n - 1 - i] == a[n - 1 - i + 1]), dp[i - 1][1] + (a[i] == a[n - 1 - i + 1]) + (a[n - 1 - i] == a[i - 1]));
            dp[i][1] += min(dp[i - 1][0] + (a[n - 1 - i] == a[i - 1]) + (a[i] == a[n - 1 - i + 1]), dp[i - 1][1] + (a[n - 1 - i] == a[n - 1 - i + 1]) + (a[i] == a[i - 1]));
        }
        int ans = min(dp[n / 2 - 1][0], dp[n / 2 - 1][1]);
        if (n % 2 == 0) {
            if (a[n / 2] == a[n / 2 - 1]) {
                ans++;
            }
        } else {
            if (a[n / 2] == a[n / 2 - 1]) {
                ans++;
            }
            if (a[n / 2] == a[n / 2 + 1]) {
                ans++;
            }
        }
        cout << ans << endl;

    }

    return 0;
}
