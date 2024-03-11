//solution for https://cses.fi/problemset/task/1635/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

ll dp[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    int c[n];
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        dp[c[i]] = 1;
    }
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i - c[j] >= 0) {
                dp[i] += dp[i - c[j]];
                dp[i] %= M;
            }
        }
    }
    cout << dp[x];
    return 0;
}
