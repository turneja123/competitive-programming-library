//https://codeforces.com/problemset/problem/739/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const double INF = 1e18;

pair<double, double> x[N];
pair<double, int> dp[N][N];

pair<double, int> calc(int n, int b, double cost) {
    dp[0][0] = make_pair(0.0, 0);
    dp[0][0] = max(dp[0][0], make_pair(x[0].first - cost, 1));
    dp[0][1] = make_pair(x[0].second, 0);
    dp[0][1] = max(dp[0][1], make_pair(1.0 - (1.0 - x[0].first) * (1.0 - x[0].second) - cost, 1));
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= min(b, i + 1); j++) {
            dp[i][j] = dp[i - 1][j];
            if (j != i + 1) {
                dp[i][j] = max(dp[i][j], make_pair(dp[i - 1][j].first + x[i].first - cost, dp[i - 1][j].second + 1));
            }
            if (j != 0) {
                dp[i][j] = max(dp[i][j], make_pair(dp[i - 1][j - 1].first + x[i].second, dp[i - 1][j - 1].second));
                dp[i][j] = max(dp[i][j], make_pair(dp[i - 1][j - 1].first + 1.0 - (1.0 - x[i].first) * (1.0 - x[i].second) - cost, dp[i - 1][j - 1].second + 1));
            }
        }
    }
    pair<double, int> ans = dp[n - 1][0];
    for (int j = 1; j <= b; j++) {
        ans = max(ans, dp[n - 1][j]);
    }
    return ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> x[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i].second;
    }
    double l = 0, r = 20.0, opt = 0;
    for (int i = 0; i < 50; i++) {
        double mid = (l + r) / 2;
        if (calc(n, b, mid).second >= a) {
            opt = mid;
            l = mid;
        } else {
            r = mid;
        }
    }
    double ans = calc(n, b, opt).first + opt * a;
    cout << ans;
    return 0;
}
