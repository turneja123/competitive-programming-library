//https://cses.fi/problemset/task/1717/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;
const int N = 1e6 + 5;

long long dp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        dp[i] = (long long)(i - 1) * (dp[i - 1] + dp[i - 2]) % M;
    }
    cout << dp[n];

    return 0;
}
