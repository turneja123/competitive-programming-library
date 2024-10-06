//https://cses.fi/problemset/task/1725/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

long double dp[6 * N];
long double dp_next[6 * N];

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(6);
    int n, a, b;
    cin >> n >> a >> b;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 6 * n; j++) {
            for (int add = 1; add <= 6; add++) {
                if (j + add > 6 * n) {
                    break;
                }
                dp_next[j + add] += dp[j] / 6.0;
            }
        }
        long double sum = 0;
        for (int j = 1; j <= 6 * n; j++) {
            sum += dp_next[j];
        }
        for (int j = 0; j <= 6 * n; j++) {
            dp[j] = dp_next[j] / sum;
            dp_next[j] = 0;
        }
    }
    long double ans = 0;
    for (int j = a; j <= b; j++) {
        ans += dp[j];
    }
    cout << ans;


    return 0;
}
