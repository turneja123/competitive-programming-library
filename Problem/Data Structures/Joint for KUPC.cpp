//https://ocpc2026w.eolymp.space/en/compete/rofq4l68mt2dp1esn9ncjjllcg/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 2e18;

const int N = 5e5 + 5;
const int K = 61;

int pref[2 * N][4];
pair<int, ll> up[K][N];

int main() {
    IOS;
    string s; ll k;
    cin >> s >> k;
    int n = s.size();
    s += s;
    for (int i = 0; i < 2 * n; i++) {
        int d = 0;
        if (s[i] == 'U') {
            d = 1;
        } else if (s[i] == 'P') {
            d = 2;
        } else if (s[i] == 'C') {
            d = 3;
        }
        pref[i][d]++;
        if (i != 0) {
            for (int j = 0; j < 4; j++) {
                pref[i][j] += pref[i - 1][j];
            }
        }
    }
    if (!(pref[n - 1][0] && pref[n - 1][1] && pref[n - 1][2] && pref[n - 1][3])) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        int l = i, r = 2 * n - 1, spl = l;
        while (l <= r) {
            int mid = (l + r) / 2;

            int ok = 1;
            for (int j = 0; j < 4; j++) {
                if (pref[mid][j] - ((i == 0 ? 0 : pref[i - 1][j])) == 0) {
                    ok = 0;
                }
            }
            if (ok) {
                spl = mid + 1;
                r = mid - 1;
            } else {
                l = mid + 1;
            }

        }
        if (spl < n) {
            up[0][i] = {spl, 0};
        } else {
            up[0][i] = {spl % n, 1};
        }
    }
    for (int j = 1; j < K; j++) {
        for (int i = 0; i < n; i++) {
            int v = up[j - 1][i].first;
            up[j][i].first = up[j - 1][v].first;
            up[j][i].second = up[j - 1][i].second + up[j - 1][v].second;
        }
    }
    ll ans = 1;
    int u = 0;
    for (int j = K - 1; j >= 0; j--) {
        ll c = (1ll << j) & k;
        if (c) {
            ans += up[j][u].second;
            u = up[j][u].first;
        }
    }
    if (u == 0) {
        ans--;
    }
    cout << ans;



    return 0;
}
