//https://qoj.ac/contest/2511/problem/14109
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

ll dp[N][64];

int main() {
    IOS;
    int n;
    cin >> n;
    n *= 2;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back({x, i});
        for (int j = 0; j < 64; j++) {
            dp[i][j] = INF;
        }
    }
    sort(a.begin(), a.end());
    dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 64; j++) {
            if (j < 32 && i > 5) {
                continue;
            }
            int j_nx = j << 1;
            if (j_nx >= 64) {
                j_nx -= 64;
            }

            dp[i][j_nx] = min(dp[i][j_nx], dp[i - 1][j]);
            for (int k = 1; k < 6; k++) {
                int c = j_nx & (1 << k);
                int bad = (a[i].second % 2 == 0 ? a[i].second + 1 : a[i].second - 1);
                if (i - k >= 0 && a[i - k].second != bad && c == 0) {
                    dp[i][(j_nx | (1 << k)) + 1] = min(dp[i][(j_nx | (1 << k)) + 1], dp[i - 1][j] + abs(a[i].first - a[i - k].first));
                }
            }
        }
    }
    if (n == 4) {
        cout << dp[n - 1][15];
    } else {
        cout << dp[n - 1][63];
    }

    return 0;
}
