//https://www.codechef.com/CDFESTMR2026/problems/JUMP12?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const ll M = 998244353;

struct Info {
    ll sumx;
    ll sumy;
    ll ct;
};

Info dp[N][2 * N];

int id(int j) {
    if (j >= 0) {
        return j;
    }
    return 2 * N + j;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int d = -(m + 2); d <= m + 2; d++) {
                dp[i][id(d)] = {0, 0, 0};
            }
        }
        for (int x = 1; x <= m; x++) {
            for (int y = 1; y <= m; y++) {
                int d = y;
                dp[1][d].ct++;
                dp[1][d].sumx += x;
                dp[1][d].sumy += x + y;
            }
        }
        for (int i = 2; i < n; i++) {
            for (int d = -(m + 2); d <= m + 2; d++) {
                int x = 0;
                int y = d;
                for (int add = 1; add <= m; add++) {
                    if (x <= y) {
                        int nw_d = x + add - y;
                        dp[i][id(nw_d)].ct = (dp[i][id(nw_d)].ct + dp[i - 1][id(d)].ct) % M;
                        dp[i][id(nw_d)].sumx = (dp[i][id(nw_d)].sumx + dp[i - 1][id(d)].sumy) % M;
                        dp[i][id(nw_d)].sumy = (dp[i][id(nw_d)].sumy + dp[i - 1][id(d)].sumx + dp[i - 1][id(d)].ct * add) % M;
                    } else {
                        int nw_d = add;
                        dp[i][id(nw_d)].ct = (dp[i][id(nw_d)].ct + dp[i - 1][id(d)].ct) % M;
                        dp[i][id(nw_d)].sumx = (dp[i][id(nw_d)].sumx + dp[i - 1][id(d)].sumy) % M;
                        dp[i][id(nw_d)].sumy = (dp[i][id(nw_d)].sumy + dp[i - 1][id(d)].sumy + dp[i - 1][id(d)].ct * add) % M;
                    }
                }
            }
        }
        ll ans = 0;
        for (int d = -(m + 2); d <= m + 2; d++) {
            ans = (ans + dp[n - 1][id(d)].sumy) % M;
        }
        cout << ans << endl;

    }

    return 0;
}
