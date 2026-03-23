//https://www.spoj.com/problems/LQDNUMS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<ll> special{9};
vector<ll> special8{8};

pair<ll, ll> dp[19][10][10][3];

ll calc(ll n) {
    vector<int> d;
    ll tmp = n;
    while (tmp > 0) {
        d.push_back(tmp % 10);
        tmp /= 10;
    }
    reverse(d.begin(), d.end());
    int m = d.size();
    for (int i = 0; i < m; i++) {
        for (int fi = 0; fi < 10; fi++) {
            for (int se = 0; se < 10; se++) {
                for (int t = 0; t < 3; t++) {
                    dp[i][fi][se][t] = {0, 0};
                }
            }
        }
    }

    for (int add = 1; add < 10; add++) {
        int t = 0;
        if (add == d[0]) {
            t = 2;
        } else if (add > d[0]) {
            t = 1;
        }
        dp[0][add][add][t].first++;
        dp[0][add][add][t].second++;
    }
    for (int i = 1; i < m; i++) {
        for (int fi = 0; fi < 10; fi++) {
            for (int se = 0; se < 10; se++) {
                for (int t = 0; t < 3; t++) {
                    for (int add = 0; add < 10; add++) {
                        int t_nx = t;
                        if (t_nx == 2) {
                            if (add < d[i]) {
                                t_nx = 0;
                            } else if (add > d[i]) {
                                t_nx = 1;
                            }
                        }
                        ll digs = dp[i - 1][fi][se][t].second + (se == add ? 0 : dp[i - 1][fi][se][t].first);

                        dp[i][fi][add][t_nx].first += dp[i - 1][fi][se][t].first;
                        dp[i][fi][add][t_nx].second += digs;
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        for (int fi = 0; fi < 10; fi++) {
            for (int se = 0; se < 10; se++) {
                for (int t = 0; t < 3; t++) {
                    if (i == m - 1 && t == 1) {
                        continue;
                    }
                    ans += dp[i][fi][se][t].second;
                    if (fi == se && i != 0) {
                        ans -= dp[i][fi][se][t].first;
                    }
                }
            }
        }
    }
    for (int i = 1; i < special.size(); i++) {
        if (special[i] < n) {
            ans++;
        }
        if (special8[i] < n) {
            ans--;
        }
    }

    if (d[0] == d.back() && n > 9) {
        ans++;
    }
    return ans;
}

int main() {
    IOS;
    for (int i = 0; i < 17; i++) {
        special.push_back(special.back() * 10 + 9);
        special8.push_back(special8.back() * 10 + 9);
    }
    ll n;
    cin >> n;
    ll l = 1, r = 1e17, ans = l;
    while (l <= r) {
        ll mid = (l + r) / 2;
        ll cur = calc(mid);
        if (cur <= n) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;

    return 0;
}
