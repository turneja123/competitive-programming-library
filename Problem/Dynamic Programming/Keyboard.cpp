//https://tlx.toki.id/problems/troc-43/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const ll INF = 1e18;

int a[N];
ll dp[N][26][26][2];
ll dp_nx[N][26][26][2];
ll cost[26][26];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - 'a';

    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            cin >> cost[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                for (int z = 0; z < 2; z++) {
                    dp[i][j][k][z] = INF;
                    dp_nx[i][j][k][z] = INF;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            dp[i][a[i]][j][0] = cost[a[i]][j];
            dp[i][j][a[i]][0] = cost[a[i]][j];
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            //a[j + i]
            int l = a[j], r = a[j + i - 1];
            ll best = INF;
            for (int k = 0; k < 26; k++) {
                for (int z = 0; z < 2; z++) {
                    int our = (z != 0 ? l : r);
                    ll add = (z != 0 ? x : 0);
                    if (k == a[j + i]) {
                        dp_nx[j][k][our][0] = min(dp_nx[j][k][our][0], dp[j][our][k][z] + add);
                    }
                    if (our == a[j + i]) {
                        dp_nx[j][our][k][0] = min(dp_nx[j][our][k][0], dp[j][our][k][z] + add);
                    }
                    best = min(best, dp[j][our][k][z] + add);
                }
            }
            for (int k = 0; k < 26; k++) {
                dp_nx[j][a[j + i]][k][0] = min(dp_nx[j][a[j + i]][k][0], best + cost[a[j + i]][k]);
            }
            //a[j]
            l = a[j + 1], r = a[j + i];
            best = INF;
            for (int k = 0; k < 26; k++) {
                for (int z = 0; z < 2; z++) {
                    int our = (z != 1 ? r : l);
                    ll add = (z != 1 ? x : 0);
                    if (k == a[j]) {
                        dp_nx[j][k][our][1] = min(dp_nx[j][k][our][1], dp[j + 1][our][k][z] + add);
                    }
                    if (our == a[j]) {
                        dp_nx[j][our][k][1] = min(dp_nx[j][our][k][1], dp[j + 1][our][k][z] + add);
                    }
                    best = min(best, dp[j + 1][our][k][z] + add);
                }
            }
            for (int k = 0; k < 26; k++) {
                dp_nx[j][a[j]][k][1] = min(dp_nx[j][a[j]][k][1], best + cost[a[j]][k]);
            }
        }
        for (int j = 0; j + i < n; j++) {
            int l = a[j], r = a[j + i];
            for (int k = 0; k < 26; k++) {
                dp[j][r][k][0] = dp_nx[j][r][k][0];
                dp_nx[j][r][k][0] = INF;

                dp[j][l][k][1] = dp_nx[j][l][k][1];
                dp_nx[j][l][k][1] = INF;
            }
        }
    }
    ll ans = INF;
    int l = a[0], r = a[n - 1];
    for (int j = 0; j < 26; j++) {
        ans = min(ans, dp[0][r][j][0]);
        ans = min(ans, dp[0][l][j][1]);

    }
    cout << ans;

    return 0;
}
