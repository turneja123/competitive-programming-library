//https://codeforces.com/contest/2201/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll M = 998244353;

ll dp[N][2];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        dp[0][1] = 1;
        int pref = 0;
        ll tot = 1, ans = 0;
        for (int i = 1; i <= n; i++) {
            ll add = (dp[i - 1][0] + dp[i - 1][1]) % M;
            if (s[i - 1] == '(') {
                ans = (ans + tot) % M;
                pref++;
            } else {
                ans = (ans + add) % M;
                pref--;
            }
            dp[i][0] = (dp[i - 1][0] + (s[i - 1] == '(' ? add : 0)) % M * (pref > 1);
            dp[i][1] = (dp[i - 1][1] + (s[i - 1] == ')' ? add : 0)) % M;
            tot = tot * 2 % M;
        }
        cout << ans << endl;
    }

    return 0;
}
