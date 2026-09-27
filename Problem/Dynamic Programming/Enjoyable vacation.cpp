//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

pair<ll, int> dp[N][2];

pair<ll, int> calc(int cost, string &s) {

    int n = s.size();
    vector<int> ones(n, 0);

    int l = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            if (s[i - 1] == '1') {
                for (int j = l; j < i; j++) {
                    ones[j] = i - l;
                }
            }
            l = i;
        }
    }
    if (s.back() == '1') {
        for (int j = l; j < n; j++) {
            ones[j] = n - l;
        }
    }
    vector<pair<int, int>> z;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            int l = (i == 0 ? 0 : ones[i - 1]);
            int r = (i == n - 1 ? 0 : ones[i + 1]);
            z.push_back({l, r});
        }
    }
    if (z.empty()) {
        return make_pair(0, 0);
    }
    int m = z.size();
    dp[0][0] = {0, 0}, dp[0][1] = {0, 0};

    for (int i = 1; i <= m; i++) {
        auto [l, r] = z[i - 1];
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        dp[i][1] = make_pair(dp[i - 1][0].first + l + r + 1 - cost, dp[i - 1][0].second + 1);
        dp[i][1] = max(dp[i][1], make_pair(dp[i - 1][1].first + r + 1 - cost, dp[i - 1][1].second + 1));
    }
    return max(dp[m][0], dp[m][1]);
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int l = 0, r = 2 * n, spl = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (calc(mid, s).second >= k) {
            spl = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    auto x = calc(spl, s);
    ll ans = x.first + (ll)spl * k;
    cout << ans;

    return 0;
}
