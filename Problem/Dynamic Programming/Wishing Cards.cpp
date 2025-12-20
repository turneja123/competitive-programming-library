//https://codeforces.com/contest/2174/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 400;
const ll INF = 1e18;

ll dp[N][N];
ll dp_nx[N][N];

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, k;
        cin >> n >> k;
        int mx = 0;
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (a > mx) {
                mx = a;
                v.push_back({i, a});
            }
        }
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -INF;
                dp_nx[i][j] = -INF;
            }
        }
        dp[0][0] = 0;

        int last = 0;
        for (int i = 0; i < v.size(); i++) {
            int d = (i == v.size() - 1 ? n : v[i + 1].first) - v[i].first;
            int a = v[i].second;
            for (int mx = 0; mx <= k; mx++) {
                for (int add = last; add <= a; add++) {
                    for (int j = add; j <= k; j++) {
                        if (dp[mx][j - add] != -INF) {
                            dp_nx[add][j] = max(dp_nx[add][j], dp[mx][j - add] + (ll)d * add);
                        }
                    }
                }
            }
            for (int mx = 0; mx <= k; mx++) {
                for (int j = 0; j <= k; j++) {
                    if (dp[mx][j] != INF) {
                        dp_nx[mx][j] = max(dp_nx[mx][j], dp[mx][j] + (ll)d * mx);
                    }
                }
            }
            for (int mx = 0; mx <= k; mx++) {
                for (int j = 0; j <= k; j++) {
                    dp[mx][j] = max(dp[mx][j], dp_nx[mx][j]);
                    dp_nx[mx][j] = -INF;
                }
            }
            last = a + 1;
        }
        ll ans = 0;
        for (int mx = 0; mx <= k; mx++) {
            for (int i = 0; i <= k; i++) {
                ans = max(ans, dp[mx][i]);
            }
        }
        cout << ans << endl;
	}

	return 0;
}
