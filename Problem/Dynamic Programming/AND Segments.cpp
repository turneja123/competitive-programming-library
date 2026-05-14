//https://codeforces.com/contest/1327/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 998244353;

ll dp[N];
ll pref[N];

ll calc(vector<tuple<int, int, int>> &v, int n) {
    vector<int> diff(n + 2, 0);
    vector<int> ival(n + 2, 0);

    int mx = -1;
    for (auto [l, r, x] : v) {
        if (x == 1) {
            diff[l]++;
            diff[r + 1]--;
        }
        if (x == 0) {
            mx = max(mx, l);
            ival[r + 1] = max(ival[r + 1], l);
        }
    }
    ll ans = 0;
    int s = 0;
    vector<int> ok(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        s += diff[i];
        ok[i] = s == 0;
    }
    dp[0] = 1;
    pref[0] = 1;
    if (mx == -1) {
        ans++;
    }
    for (int i = 1, l = 0; i <= n; i++) {
        l = max(l, ival[i]);
        if (!ok[i]) {
            dp[i] = 0;
        } else {
            dp[i] = (pref[i - 1] - (l == 0 ? 0 : pref[l - 1]) + M) % M;
        }
        if (mx <= i) {
            ans = (ans + dp[i]) % M;
        }
        pref[i] = (pref[i - 1] + dp[i]) % M;
    }
    return ans;
}


int main() {
    IOS;
    int n, k, m;
    cin >> n >> k >> m;

    vector<tuple<int, int, int>> v;
    for (int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        v.push_back({l, r, x});
    }
    ll ans = 1;
    for (int i = 0; i < k; i++) {
        vector<tuple<int, int, int>> cur = v;
        for (int j = 0; j < m; j++) {
            int c = (1 << i) & get<2>(cur[j]);
            c = min(c, 1);
            get<2>(cur[j]) = c;
        }
        ans = ans * calc(cur, n) % M;
    }
    cout << ans;



    return 0;
}
