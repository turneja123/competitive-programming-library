//https://codeforces.com/contest/1218/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const ll INF = 1e18;

ll dp[2][N][N][2]; //red, kolona, koliko puta je isti potez bio za redom, koji potez
ll cost[N][N];

vector<pair<int, int>> bonus[N][N][2];

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x[4], y[4], d, t, e;
        cin >> x[0] >> y[0] >> d >> t >> e;
        int ok[4] = {};
        x[1] = x[0] + d, y[1] = y[0] - d;
        x[2] = x[0] + d, y[2] = y[0];
        x[3] = x[0], y[3] = y[0] + d;

        for (int j = 0; j < 4; j++) {
            if (x[j] + y[j] >= t + j && (x[j] + y[j]) % 4 == (t + j) % 4) {
                ok[j] = 1;
                cost[x[j]][y[j]] += e;
            }
        }

        if (ok[1] && ok[2]) {
            bonus[x[2]][y[2]][1].push_back({d - 1, e});   //ide za redom d puta desno
        }
        if (ok[0] && ok[3]) {
            bonus[x[3]][y[3]][1].push_back({d - 1, e});   //ide za redom d puta desno
        }
        if (ok[0] && ok[2]) {
            bonus[x[2]][y[2]][0].push_back({d - 1, e});   //ide za redom d puta dole
        }
    }
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < max(n, m); k++) {
            dp[0][j][k][0] = INF;
            dp[0][j][k][1] = INF;
            dp[1][j][k][0] = INF;
            dp[1][j][k][1] = INF;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < max(n, m); k++) {
                dp[i % 2][j][k][0] = INF;
                dp[i % 2][j][k][1] = INF;
            }
        }
        for (int j = 0; j < m; j++) {
            if (bonus[i][j][0].size()) {
                sort(bonus[i][j][0].begin(), bonus[i][j][0].end());
            }
            if (bonus[i][j][1].size()) {
                sort(bonus[i][j][1].begin(), bonus[i][j][1].end());
            }
            if (i == 0 && j == 0) {
                dp[0][0][0][0] = cost[i][j];
                dp[0][0][0][1] = cost[i][j];
                continue;
            }

            if (j != 0) { //od onog levo
                //od za redom dole
                int ptr = 0;
                ll s = 0;
                for (int k = 0; k < max(n, m); k++) {
                    if (dp[i % 2][j - 1][k][0] == INF) {
                        continue;
                    }
                    while (ptr < bonus[i][j][1].size() && bonus[i][j][1][ptr].first == 0) {
                        s += bonus[i][j][1][ptr].second;
                        ptr++;
                    }
                    dp[i % 2][j][1][1] = min(dp[i % 2][j][1][1], dp[i % 2][j - 1][k][0] + cost[i][j] - s);

                }
                //od za redom desno
                for (int k = 1; k < max(n, m); k++) {
                    if (dp[i % 2][j - 1][k - 1][1] == INF) {
                        continue;
                    }
                    while (ptr < bonus[i][j][1].size() && bonus[i][j][1][ptr].first <= k - 1) {
                        s += bonus[i][j][1][ptr].second;
                        ptr++;
                    }
                    dp[i % 2][j][k][1] = min(dp[i % 2][j][k][1], dp[i % 2][j - 1][k - 1][1] + cost[i][j] - s);
                }
            }
            if (i != 0) { //od onog gore
                //od za redom desno
                int ptr = 0;
                ll s = 0;
                for (int k = 0; k < max(n, m); k++) {
                    if (dp[(i + 1) % 2][j][k][1] == INF) {
                        continue;
                    }
                    while (ptr < bonus[i][j][0].size() && bonus[i][j][0][ptr].first == 0) {
                        s += bonus[i][j][0][ptr].second;
                        ptr++;
                    }
                    dp[i % 2][j][1][0] = min(dp[i % 2][j][1][0], dp[(i + 1) % 2][j][k][1] + cost[i][j] - s);
                }
                //od za redom dole
                for (int k = 1; k < max(n, m); k++) {
                    if (dp[(i + 1) % 2][j][k - 1][0] == INF) {
                        continue;
                    }
                    while (ptr < bonus[i][j][0].size() && bonus[i][j][0][ptr].first <= k - 1) {
                        s += bonus[i][j][0][ptr].second;
                        ptr++;
                    }
                    dp[i % 2][j][k][0] = min(dp[i % 2][j][k][0], dp[(i + 1) % 2][j][k - 1][0] + cost[i][j] - s);
                }
            }
        }
    }
    ll ans = INF;
    for (int k = 0; k < max(n, m); k++) {
        ans = min({ans, dp[(n - 1) % 2][m - 1][k][0], dp[(n - 1) % 2][m - 1][k][1]});
    }

    cout << ans;

    return 0;
}
