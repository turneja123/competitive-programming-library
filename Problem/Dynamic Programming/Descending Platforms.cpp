//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-2/problems/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1500000;
const ll INF = 1e18;

ll dp[N];
int go[N];


int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n; ll m;
        cin >> n >> m;
        ll ans = INF;
        int lim = min((ll)m + n, (ll)n * n + 100);
        vector<pair<ll, int>> items;
        ld best = 0; int k; ll pref = 0;
        for (int i = 0; i < n; i++) {
            ll a;
            cin >> a;
            pref += a;
            items.push_back({pref, i + 1});
            if ((ld)pref / (ld)(i + 1) > best) {
                k = i;
                best = (ld)pref / (ld)(i + 1);
            }
        }
        for (int j = 0; j <= lim; j++) {
            dp[j] = -INF;
        }
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            auto [v, w] = items[i];
            for (int j = w; j <= lim; j++) {
                if (dp[j - w] != -INF && dp[j] < dp[j - w] + v) {
                    dp[j] = dp[j - w] + v;
                    go[j] = j - w;
                }
            }
        }
        int i; ll add;
        for (int j = 0; j <= lim; j++) {
            if (dp[j] == -INF) {
                continue;
            }
            if (dp[j] < m) {
                auto [v, w] = items[k];
                ll ct = (m - dp[j] + v - 1) / v;
                if (j + w * ct < ans) {
                    ans = j + w * ct;
                    add = ct;
                    i = j;
                }
            } else {
                if (ans > j) {
                    ans = j;
                    i = j;
                    add = 0;
                }
            }
        }
        vector<ll> b(n);
        b[k] += add;
        while (i != 0) {
            int j = go[i];
            b[i - j - 1]++;
            i = j;
        }
        for (int i = n - 2; i >= 0; i--) {
            b[i] += b[i + 1];
        }
        cout << "Case #" << tt << ": " << ans << endl;
        for (int i = 0; i < n; i++) {
            cout << b[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
