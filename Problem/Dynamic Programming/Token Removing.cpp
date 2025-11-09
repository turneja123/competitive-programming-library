//https://codeforces.com/problemset/problem/2119/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

ll dp[N];
ll dp_nx[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, M;
        cin >> n >> M;
        dp[0] = 1, dp[1] = n;
        for (int i = n - 1; i > 0; i--) {
            for (int j = 0; j <= n - i; j++) {
                dp_nx[j] = (dp_nx[j] + dp[j]) % M;
                dp_nx[j + 1] = (dp_nx[j + 1] + dp[j] * i % M * (n - i - j + 1)) % M;
            }
            for (int j = 0; j <= n - i + 1; j++) {
                dp[j] = dp_nx[j];
                dp_nx[j] = 0;
            }
        }
        ll ans = 0;
        for (int j = 0; j <= n; j++) {
            ans = (ans + dp[j]) % M;
        }
        cout << ans << endl;
    }

    return 0;
}
