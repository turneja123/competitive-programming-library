//https://codeforces.com/gym/105698/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 7005;
const long long M = 998244353;

int a[N];
long long dp[N][N];
long long pref[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
        pref[i][0] = 1;
        for (int j = i - 1; j > 0; j--) {
            int k = upper_bound(a + 1, a + 1 + n, a[i] - a[j]) - a - 1;
            k = min(k, j - 1);
            dp[i][j] = pref[j][k];
        }
        for (int j = 1; j <= i; j++) {
            pref[i][j] = (pref[i][j - 1] + dp[i][j]) % M;
        }
        ans = (ans + pref[i][i]) % M;
    }
    cout << ans;
    return 0;
}
