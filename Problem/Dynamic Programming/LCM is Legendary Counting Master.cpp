//https://codeforces.com/contest/2183/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const ll M = 998244353;

int a[N];
ll dp[N][N];
vector<int> divs[N];


int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            for (int j = 0; j <= m; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][1] = a[0] <= 1;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int d : divs[j]) {
                    if (j + d <= m) {
                        dp[i][j + d] = (dp[i][j + d] + dp[i - 1][j] * ((a[i] == j + d || a[i] == 0) ? 1 : 0)) % M;
                    }
                }
            }
        }
        ll ans = 0;
        for (int j = 1; j <= m; j++) {
            ans = (ans + dp[n - 1][j]) % M;
        }
        cout << ans << endl;

    }
    return 0;
}
