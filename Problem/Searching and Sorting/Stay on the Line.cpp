//https://tlx.toki.id/contests/troc-42/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

pair<int, int> a[N];

vector<pair<int, int>> X;
vector<pair<int, int>> Y;

int main() {
    IOS;
    int n, m, x, y;
    cin >> n >> n >> x >> y;
    for (int i = 0; i < n; i++) {
        int t, k;
        cin >> t >> k;
        a[i] = {t, k};
        if (t == 1) {
            X.push_back({i, k});
        } else {
            Y.push_back({i, k});
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        auto [t, k] = a[i];

        if (t == 1) {
            int diff = abs(x - k);
            ans += diff;
            x = k;
            int jy = lower_bound(Y.begin(), Y.end(), make_pair(i, N)) - Y.begin();
            if (jy != Y.size()) {
                int z = Y[jy].second;
                if (z >= y) {
                    y += min(z - y, diff);
                } else {
                    y -= min(y - z, diff);
                }
            }
        } else {
            int diff = abs(y - k);
            ans += diff;
            y = k;
            int jx = lower_bound(X.begin(), X.end(), make_pair(i, N)) - X.begin();
            if (jx != X.size()) {
                int z = X[jx].second;
                if (z >= x) {
                    x += min(z - x, diff);
                } else {
                    x -= min(x - z, diff);
                }
            }
        }
    }
    cout << ans;
    return 0;
}
