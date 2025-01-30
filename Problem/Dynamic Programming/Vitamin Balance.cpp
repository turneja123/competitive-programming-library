//https://atcoder.jp/contests/abc390/tasks/abc390_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

int sum[N];
vector<pair<int, int>> a[3];
int dp[N][N][3];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        int v, aa, c;
        cin >> v >> aa >> c;
        v--;
        a[v].push_back(make_pair(aa, c));
        sum[v] += aa;
    }
    if (a[0].empty() || a[1].empty() || a[2].empty()) {
        cout << 0;
        return 0;
    }
    for (int v = 0; v < 3; v++) {
        dp[0][0][v] = 0;
        dp[0][a[v][0].second][v] = a[v][0].first;
        for (int i = 1; i < a[v].size(); i++) {
            for (int j = 0; j <= x; j++) {
                dp[i][j][v] = max(dp[i][j][v], dp[i - 1][j][v]);
                if (j + a[v][i].second <= x) {
                    dp[i][j + a[v][i].second][v] = max(dp[i][j + a[v][i].second][v], dp[i - 1][j][v] + a[v][i].first);
                }
            }
        }
    }
    int l = 1, r = min({sum[0], sum[1], sum[2]}), ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        int need = 0;
        for (int v = 0; v < 3; v++) {
            int n = a[v].size();
            bool f = false;
            for (int j = 0; j <= x; j++) {
                if (dp[n - 1][j][v] >= mid) {
                    need += j;
                    f = true;
                    break;
                }
            }
            if (!f) {
                need = N;
                break;
            }
        }
        if (need <= x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;

    return 0;
}
