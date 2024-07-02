//https://atcoder.jp/contests/abc207/tasks/abc207_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const long long M = 1e9 + 7;

long long a[N];
long long dp[N][N];
long long aux[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        dp[i][1] = 1;
        sum += a[i];
        for (int j = 2; j <= n; j++) {
            dp[i][j] = aux[j][sum % j];
        }
        for (int j = 2; j <= n; j++) {
            aux[j][sum % j] = (aux[j][sum % j] + dp[i][j - 1]) % M;
        }
    }
    long long ans = 0;
    for (int j = 1; j <= n; j++) {
        ans += dp[n][j];
    }
    cout << ans % M;


    return 0;
}
