//https://atcoder.jp/contests/abc314/tasks/abc314_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

long double dp[N];
int c[N];
int p[N];
vector<int> a[N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        cin >> p[i];
        a[i].resize(p[i]);
        for (int j = 0; j < p[i]; j++) {
            cin >> a[i][j];
        }
    }
    dp[0] = 0;
    for (int k = 1; k <= m; k++) {
        dp[k] = (long double)1e18;
        for (int i = 0; i < n; i++) {
            long double sum = 0, zero = 0;
            for (int j = 0; j < p[i]; j++) {
                if (a[i][j] == 0) {
                    zero += (long double)1.0 / (long double)p[i];
                } else {
                    sum += dp[max(0, k - a[i][j])] / (long double)p[i];
                }
            }
            dp[k] = min(dp[k], (c[i] + sum) / ((long double)1.0 - zero));
        }
    }
    cout << dp[m];
    return 0;
}
