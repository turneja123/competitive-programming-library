//https://codeforces.com/contest/2165/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 998244353;

int dp[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<int> v;
        int last = a[0], ct = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] != last) {
                v.push_back(ct);
                last = a[i];
                ct = 1;
            } else {
                ct++;
            }
        }
        v.push_back(ct);
        sort(v.begin(), v.end());
        int m = v.size();
        ll ans = v.back();
        for (int i = 0; i < m - 1; i++) {
            ans = ans * (v[i] + 1) % M;
        }
        if (m == 1) {
            cout << ans << endl;
            continue;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][v[0]] = v[0];
        dp[0][0] = 1;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 0; j <= n; j++) {
                if (j + v[i] <= n) {
                    dp[i][j + v[i]] = (dp[i][j + v[i]] + (ll)dp[i - 1][j] * v[i]) % M;
                }
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % M;
            }
        }
        for (int j = v.back(); j <= n; j++) {
            ans = (ans + dp[m - 2][j]) % M;
        }
        cout << ans << endl;

    }
    return 0;
}
