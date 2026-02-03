//https://ocpc2026w.eolymp.space/en/compete/7ds15ifh194hve0pf1tgf05pqs/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 998244353;

int l[N], r[N];
ll dep[N];
ll dp[N][N];
ll pref[N][N];
ll inv[N];

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = l[i]; j <= r[i]; j++) {
            dep[i] = (dep[i] + (dep[j] + 1) * inv[r[i] - l[i] + 1]) % M;
        }
        ans = (ans + dep[i]) % M;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            dp[i][j] = (pref[i][r[j]] - (l[j] == 0 ? 0 : pref[i][l[j] - 1]) + M) * inv[r[j] - l[j] + 1] % M;
            pref[i][j] = (pref[i][j - 1] + dp[i][j]) % M;
            pref[j][i] = ((i == 0 ? 0 : pref[j][i - 1]) + dp[i][j]) % M;
            ans = (ans - 2 * dp[i][j] % M * inv[n - 1] % M + M) % M;
        }
        dp[j][j] = dep[j];
        pref[j][j] = (pref[j][j - 1] + dep[j]);
    }
    cout << ans;



    return 0;
}
