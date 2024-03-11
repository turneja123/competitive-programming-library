//solution for https://dmoj.ca/problem/wac6p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll calc(string a, string b)
{
    int n = a.size();
    int m = b.size();
    ll dp[n + 1][m + 1];
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % M;
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][m];
}

ll sum(ll n) {
    ll ret = n * (n + 1) / 2;
    ret %= M;
    return ret;
}

int main() {
    IOS;
    ll n, k;
    string s;
    cin >> n >> k >> s;
    ll ct_w = calc(s, "W");
    ll ct_a = calc(s, "A");
    ll ct_c = calc(s, "C");
    ll ct_wa = calc(s, "WA");
    ll ct_ac = calc(s, "AC");
    ll ct_wac = calc(s, "WAC");
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans += ct_wac;
        ans %= M;
        ans += ((ct_wa * (k - i - 1) % M) * ct_c) % M;
        ans %= M;
        ans += ((ct_w * (k - i - 1) % M) * ct_ac) % M;
        ans %= M;
        ans += (((((ct_w * ct_a) % M) * ct_c) % M) * sum(k - 2 - i)) % M;
        ans %= M;

    }
    cout << ans << endl;

    return 0;
}
