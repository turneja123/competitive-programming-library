//https://codeforces.com/contest/2107/problem/F1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

long long a[N];
long long dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i] = INF;
        }
        for (int i = 1; i <= n; i++) {
            long long m = a[i] + 1, cur = a[i];
            dp[i] = min(dp[i], dp[i - 1] + cur);
            for (int j = i - 1; j >= 1; j--) {
                cur += m;
                cur = min(cur, (a[j] + 1) * (i - j + 1) + i - j - 1);
                m = min(m, a[j] + 1);
                dp[i] = min(dp[i], dp[j - 1] + cur);
            }

        }
        cout << dp[n] << endl;
    }


    return 0;
}
