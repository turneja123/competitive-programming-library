//https://www.spoj.com/problems/TSPMOHUG/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int c[N];
int dp[N];

int calc(int i, int n) {
    if (i >= n) {
        return 0;
    }
    if (dp[i] != -1) {
        return dp[i];
    }
    return dp[i] = max(calc(i + 1, n), a[i] + calc(i + 1 + c[i], n));
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
        dp[i] = -1;
    }
    int ans = calc(0, n);
    cout << ans;
    return 0;
}
