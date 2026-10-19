//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int dp[N][4];

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
        for (int j = 0; j < 4; j++) {
            dp[i][j] = N;
        }
    }
    for (int i = 0; i < 8; i++) {
        if (__builtin_popcount(i) % 2 == 0) {

            int s0 = min(1, i & 4);
            int s1 = min(1, i & 2);
            int s2 = i & 1;
            int cost = (a[0] != s0) + (a[1] != s1) + (a[2] != s2);
            dp[2][i & 3] = min(dp[2][i & 3], cost);
        }
    }
    for (int i = 3; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (__builtin_popcount(j) % 2 == 0) {
                int mask = j << 1;
                int cost = (a[i] != 0);
                dp[i][mask & 3] = min(dp[i][mask & 3], dp[i - 1][j] + cost);
            } else {
                int mask = (j << 1) + 1;
                int cost = (a[i] != 1);
                dp[i][mask & 3] = min(dp[i][mask & 3], dp[i - 1][j] + cost);
            }
        }
    }
    cout << min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2], dp[n - 1][3]});



    return 0;
}
