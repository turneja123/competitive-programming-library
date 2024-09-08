//https://cses.fi/problemset/task/1097/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

int a[N];
long long dp[N][N];

long long calc(int l, int r, int flag) {
    if (l > r) {
        return 0;
    }
    if (dp[l][r] != INF) {
        return dp[l][r];
    }
    if (flag == 0) {
        return dp[l][r] = min(calc(l + 1, r, flag ^ 1), calc(l, r - 1, flag ^ 1));
    } else {
        return dp[l][r] = max(a[l] + calc(l + 1, r, flag ^ 1), a[r] + calc(l, r - 1, flag ^ 1));
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }
    cout << max(a[0] + calc(1, n - 1, 0), a[n - 1] + calc(0, n - 2, 0));
    return 0;
}
