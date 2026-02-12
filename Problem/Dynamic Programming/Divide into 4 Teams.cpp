//https://atcoder.jp/contests/arc214/tasks/arc214_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 998244353;

int a[N];
ll dp[N];

int main() {
    IOS;
    int n, s = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = s - a[i]; j >= 0; j--) {
            dp[j + a[i]] = (dp[j + a[i]] + dp[j]) % M;
        }
    }
    if (s % 2 == 1) {
        cout << 0;
    } else {
        cout << dp[s / 2] * (dp[s / 2] - 2) % M;
    }


    return 0;
}
