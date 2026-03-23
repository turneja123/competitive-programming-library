//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-r5k77aLPrxeUfu7PRiT9T
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int M = 5005;
const int INF = 1e9 + 1;

pair<int, int> a[N];
tuple<int, int, int> b[M];

ll dp[M][M];

int main() {
    IOS;
    int n, m, w;
    cin >> n >> m >> w;


    ll best = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = n + 1; i < M; i++) {
        a[i] = a[(i - 1) % n + 1];
    }
    vector<ll> healths(M, 0);
    for (int i = 1; i < M; i++) {
        healths[i] = healths[i - 1] + a[i].first;
    }
    for (int i = 1; i <= m; i++) {
        int h, d, c;
        cin >> h >> d >> c;
        b[i] = {h, d, c};
    }
    for (int i = 1; i <= m; i++) {
        auto [h, d, c] = b[i];
        for (int j = 0; j <= w; j++) {
            dp[i][j] = dp[i - 1][j];
        }

        for (int j = 0; j <= w - c; j++) {
            ll hp = dp[i - 1][j];
            int k = upper_bound(healths.begin(), healths.end(), hp) - healths.begin();
            auto [mh, md] = a[k];
            mh -= hp - healths[k - 1];

            int turns_i_get = (md == 0 ? INF : (h + md - 1) / md - 1);
            ll dmg = (ll)turns_i_get * d;
            if (dmg < mh) {
                ll tot = hp + dmg;
                if (tot > best) {
                    best = tot;
                }
                dp[i][j + c] = max(dp[i][j + c], hp + dmg);
            } else {
                ll tot = hp + mh;
                if (tot > best) {
                    best = tot;
                }
                dp[i][j + c] = max(dp[i][j + c], hp + mh);
            }
        }
    }
    int k = upper_bound(healths.begin(), healths.end(), best) - healths.begin();

    cout << best - healths[k - 1] << " " << best;
    return 0;
}
