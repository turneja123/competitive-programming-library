//https://codeforces.com/contest/2125/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;
const ll INFLL = 1e18;

int ct[N];
int diff[N];
pair<ll, int> dp[N][6];

string d = "docker";
string s;

pair<ll, int> calc(int n, int cost_a) {
    dp[0][0] = {0, 0};
    for (int j = 1; j < 6; j++) {
        dp[0][j] = {INFLL, 0};
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = {INFLL, 0};
        pair<ll, int> mn = dp[i - 1][0];

        for (int j = 1; j < 6; j++) {
            mn = min(mn, dp[i - 1][j]);
            dp[i][j] = make_pair(dp[i - 1][j - 1].first + (s[i - 1] != d[j - 1]), dp[i - 1][j - 1].second);

        }
        dp[i][0] = min(dp[i][0], make_pair(dp[i - 1][0].first + (s[i - 1] == d[0]), dp[i - 1][0].second));
        for (int j = 1; j < 5; j++) {
            dp[i][0] = min(dp[i][0], make_pair(dp[i - 1][j].first + (s[i - 1] == d[j]) + (s[i - 1] == d[0]), dp[i - 1][j].second));
        }
        dp[i][0] = min(dp[i][0], make_pair(dp[i - 1][5].first + (s[i - 1] == d[5]) + (s[i - 1] == d[0]), dp[i - 1][5].second));
        dp[i][0] = min(dp[i][0], make_pair(dp[i - 1][5].first + (s[i - 1] != d[5]) + cost_a, dp[i - 1][5].second - 1));
        dp[i][1] = min(dp[i][1], make_pair(mn.first + (s[i - 1] != d[0]), mn.second));
    }
    pair<ll, int> ans = {INFLL, 0};
    for (int j = 0; j < 6; j++) {
        ans = min(ans, dp[n][j]);
    }
    return ans;

}

int calc_ter(int n, int k) {

    int l = -n, r = n, opt = r;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (-calc(n, mid).second >= k) {
            opt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return calc(n, opt).first - (ll)k * opt;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        int n = s.size();
        for (int i = 0; i <= n + 1; i++) {
            diff[i] = 0;
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            r = min(r, n / 6);
            if (l > r) {
                continue;
            }
            diff[l]++;
            diff[r + 1]--;
        }
        if (n < 6) {
            cout << 0 << endl;
            continue;
        }

        int su = 0, mx = 0;
        for (int i = 0; i <= n / 6; i++) {
            su += diff[i];
            mx = max(mx, su);
            ct[i] = su;
        }
        vector<int> inds;
        for (int i = 0; i <= n / 6; i++) {
            if (ct[i] == mx) {
                inds.push_back(i);
            }
        }
        if (mx == 0) {
            cout << 0 << endl;
            continue;
        }
        int spl = -calc(n, 0).second;
        int try_left = -1, try_right = n + 1;
        for (int i : inds) {

            if (i <= spl) {
                try_left = max(try_left, i);
            } else {
                try_right = min(try_right, i);
            }
        }
        int ans = INF;
        if (try_left != -1) {
            ans = min(ans, calc_ter(n, try_left));
        }
        if (try_right != n + 1) {
            ans = min(ans, calc_ter(n, try_right));
        }
        cout << ans << endl;
    }
    return 0;
}
