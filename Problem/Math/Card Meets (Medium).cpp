//https://www.spoj.com/problems/GUMATH2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 10000009;

long long dp[M * 2];

int main() {
    IOS;
    dp[0] = 1, dp[1] = 0;
    for (long long i = 2; i < M * 2; i++) {
        dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long ans = (n % M) * dp[(n - 1) % (M * 2)] % M;
        cout << ans << endl;
    }
    return 0;
}
