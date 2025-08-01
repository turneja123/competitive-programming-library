//https://www.spoj.com/problems/UNICA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll __int128
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

ll inf = 1e10;

ll dp[70][7][7][7][3];
vector<int> add{-1,1};

ll calc(ll n) {
    vector<int> d;
    while (n > 0) {
        d.push_back(n % 2);
        n /= 2;
    }
    reverse(d.begin(), d.end());
    d.erase(d.begin());
    int m = d.size();
    if (d[0] == 1) {
        dp[0][3 + 1][3 + 1][3][2] = 1;
        dp[0][3 - 1][3][3 - 1][0] = 1;
    } else {
        dp[0][3 + 1][3 + 1][3][1] = 1;
        dp[0][3 - 1][3][3 - 1][2] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < 7; j++) {
            for (int b = 0; b < 2; b++) {
                for (int mx = 0; mx < 7; mx++) {
                    for (int mn = 0; mn < 7; mn++) {
                        int j_nx = j + add[b];
                        if (j_nx < 0 || j_nx >= 7) {
                            continue;
                        }
                        int d1 = j_nx - mx;
                        int d2 = j_nx - mn;
                        if (d1 < -3 || d2 > 3) {
                            continue;
                        }
                        if (b < d[i]) {
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][0] += dp[i - 1][j][mx][mn][0] + dp[i - 1][j][mx][mn][2];
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][1] += dp[i - 1][j][mx][mn][1];
                        } else if (b > d[i]) {
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][1] += dp[i - 1][j][mx][mn][1] + dp[i - 1][j][mx][mn][2];
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][0] += dp[i - 1][j][mx][mn][0];
                        } else {
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][0] += dp[i - 1][j][mx][mn][0];
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][1] += dp[i - 1][j][mx][mn][1];
                            dp[i][j + add[b]][max(j_nx, mx)][min(j_nx, mn)][2] += dp[i - 1][j][mx][mn][2];
                        }
                    }
                }
            }

        }
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 7; j++) {
            for (int mx = 0; mx < 7; mx++) {
                for (int mn = 0; mn < 7; mn++) {
                    ans += dp[i][j][mx][mn][0] + dp[i][j][mx][mn][2];
                    if (i < m - 1) {
                        ans += dp[i][j][mx][mn][1];
                    }



                    dp[i][j][mx][mn][0] = 0;
                    dp[i][j][mx][mn][1] = 0;
                    dp[i][j][mx][mn][2] = 0;
                }
            }
        }
    }
    return ans;
}


int main() {
    IOS;
    long long n;
    cin >> n;
    ll l = 2, r = inf * inf, m = 0;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll ct = calc(mid);
        if (ct >= n) {
            m = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }

    }
    vector<int> d;
    while (m > 0) {
        d.push_back(m % 2);
        m /= 2;
    }
    reverse(d.begin(), d.end());
    for (int i = 1; i < d.size(); i++) {
        char c = 'a' + d[i];
        cout << c;
    }
    return 0;
}
