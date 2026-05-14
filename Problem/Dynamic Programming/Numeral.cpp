//https://atcoder.jp/contests/ndpc/tasks/ndpc2026_m
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 22;
const int M = 998244353;

int a[1 << N];
int dp[N + 1][1 << N];
int ct[N + 1][1 << N];

int pw[(1 << N) + 1];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll ans = 0;
    pw[0] = 1;
    for (int i = 0; i < 1 << n; i++) {
        a[i] = s[i] - '0';
        pw[i + 1] = (ll)pw[i] * 10 % M;
        int t = 0;
        for (int j = n - 1; j >= 0; j--) {
            int mask = i ^ (1 << j);
            if (mask > i) {
                continue;
            }
            ct[t][i] = ct[t][mask];
            dp[t][i] = dp[t][mask];
            t++;
        }
        for (int j = t - 1; j >= 0; j--) {
            dp[j][i] = ((ll)dp[j][i] * pw[ct[j + 1][i]] + dp[j + 1][i]) % M;
            ct[j][i] = ct[j][i] + ct[j + 1][i];

        }
        for (int j = 0; j <= t; j++) {
            dp[j][i] = ((ll)dp[j][i] * 10 + a[i]) % M;
            ct[j][i]++;
        }
        ans += dp[0][i] ^ i;
    }
    cout << ans << endl;
    return 0;
}
