//https://codeforces.com/contest/1279/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];
pair<long long, int> dp[N];

pair<long long, int> calc(int n, int l, int f, long long cost) {
    dp[0] = make_pair((a[0] != f ? 1 : 0), 0);
    if (l == 1) {
        dp[0] = min(dp[0], make_pair(cost, -1));
    }
    for (int i = 1; i < n; i++) {
        dp[i] = make_pair(dp[i - 1].first + (a[i] != f ? 1 : 0), dp[i - 1].second);
        if (i <= l - 1) {
            dp[i] = min(dp[i], make_pair(cost, -1));
        } else {
            dp[i] = min(dp[i], make_pair(dp[i - l].first + cost, dp[i - l].second - 1));
        }

    }
    return dp[n - 1];
}

int main() {
    IOS;
    int n, k, sz;
    cin >> n >> k >> sz;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] >= 'a') {
            a[i] = 1;
        } else {
            a[i] = 0;
        }
    }
    long long l = 0, r = 1e16, opt = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        pair<long long, int> ans = min(calc(n, sz, 0, mid), calc(n, sz, 1, mid));
        ans.second *= -1;
        if (ans.second >= k) {
            opt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    long long ans = min(calc(n, sz, 0, opt).first, calc(n, sz, 1, opt).first) - opt * k;
    cout << ans;
    return 0;
}
