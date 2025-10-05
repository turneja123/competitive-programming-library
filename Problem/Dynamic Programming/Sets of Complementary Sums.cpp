//https://codeforces.com/contest/2125/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll dp[N];
ll dp_residue[N];
ll dp_nx[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        ll s = (ll)n * (n + 1) / 2;
        if (n == 1) {
            cout << x << endl;
            continue;
        }
        if (s - 1 > x) {
            cout << 0 << endl;
            continue;
        }
        dp[s - 1] = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= x; j++) {
                dp_residue[j % i] = (dp_residue[j % i] + dp[j]) % M;
                dp[j] = dp_residue[j % i];
            }
            for (int j = 0; j <= x; j++) {
                dp_residue[j] = 0;
            }
        }
        ll ans = 0;
        for (int j = 1; j <= x; j++) {
            ans = (ans + dp[j] * (x - j + 1)) % M;
            dp[j] = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
