//https://atcoder.jp/contests/abc335/tasks/abc335_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = sqrt(N);
const long long M = 998244353;

int a[N];
long long dp[N];
long long aux[N][SQ];

int main() {
    IOS;
    int n, sq;
    cin >> n;
    sq = sqrt(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < sq; j++) {
            dp[i] = (dp[i] + aux[j][i % j]) % M;
        }
        if (a[i] >= sq) {
            for (int j = i + a[i]; j < n; j += a[i]) {
                dp[j] = (dp[j] + dp[i]) % M;
            }
        } else {
            aux[a[i]][i % a[i]] = (aux[a[i]][i % a[i]] + dp[i]) % M;
        }
        ans = (ans + dp[i]) % M;
    }
    cout << ans << endl;

    return 0;
}
