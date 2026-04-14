//https://codeforces.com/contest/1337/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int M = 998244353;

int dp[N][N];

int main() {
    IOS;
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();

    for (int j = 0; j < n; j++) {
        if (!(j < m && a[0] != b[j])) {
            dp[0][j] = 2;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(j < m && a[i] != b[j])) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % M;
            }
            if (j + i < n && !(j + i < m && a[i] != b[j + i])) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
            }
        }
    }
    int ans = 0;
    for (int i = m - 1; i < n; i++) {
        ans = (ans + dp[i][0]) % M;
    }
    cout << ans;

    return 0;
}
