//https://codeforces.com/contest/575/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;

ll dp[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    vector<int> compr{x};
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        compr.push_back(l);
        compr.push_back(r);
        a[i] = {l, r};
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    int m = compr.size();
    for (int i = 0; i < m; i++) {
        dp[i] = abs(compr[i] - x);
    }

    auto id = [&](int i) -> int {
        return lower_bound(compr.begin(), compr.end(), i) - compr.begin();
    };

    for (int i = 0; i < n; i++) {
        auto [l, r] = a[i];
        l = id(l);
        r = id(r);
        for (int i = l - 1; i >= 0; i--) {
            dp[i] += compr[l] - compr[i];
            dp[i] = min(dp[i], dp[i + 1] + compr[i + 1] - compr[i]);
        }
        for (int i = r + 1; i < m; i++) {
            dp[i] += compr[i] - compr[r];
            dp[i] = min(dp[i], dp[i - 1] + compr[i] - compr[i - 1]);
        }
    }
    ll ans = 1e18;
    for (int i = 0; i < m; i++) {
        ans = min(ans, dp[i]);
    }
    cout << ans;

    return 0;
}
