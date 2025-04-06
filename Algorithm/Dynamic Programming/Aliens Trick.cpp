//https://oj.uz/problem/view/NOI19_feast
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

long long a[N];
pair<long long, int> dp[N][2];

pair<long long, int> calc(int n, long long cost) {
    dp[0][0] = make_pair(0, 0);
    dp[0][1] = make_pair(a[0] - cost, 1);
    for (int i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = max(make_pair(dp[i - 1][1].first + a[i], dp[i - 1][1].second), make_pair(dp[i - 1][0].first + a[i] - cost, dp[i - 1][0].second + 1));
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    int ct = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) {
            ct++;
        }
    }
    k = min(k, ct);
    long long l = 0, r = 1e16, opt = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (calc(n, mid).second >= k) {
            opt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    long long ans = calc(n, opt).first + opt * k;
    cout << ans;
    return 0;
}
