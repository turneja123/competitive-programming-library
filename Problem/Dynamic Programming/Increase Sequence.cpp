//https://codeforces.com/contest/466/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int M = 1e9 + 7;

int dp[N][N];

int main() {
    IOS;
    int n, h;
    cin >> n >> h;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (a[0] > h) {
        cout << 0;
        return 0;
    }
    if (a[0] == h) {
        dp[0][0] = 1;
    } else if (a[0] == h - 1) {
        dp[0][0] = 1;
        dp[0][1] = 1;
    } else {
        cout << 0;
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if (a[i] > h) {
            cout << 0;
            return 0;
        }
        int j = h - a[i];
        dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M; //00
        if (j - 1 >= 0) {
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % M; //10
        }
        if (j != 0) {
            dp[i][j - 1] = (dp[i][j - 1] + (long long)j * dp[i - 1][j] % M) % M; //01
            dp[i][j - 1] = (dp[i][j - 1] + (long long)j * dp[i - 1][j - 1] % M) % M; //11
        }
    }
    cout << dp[n - 1][0];
    return 0;
}
