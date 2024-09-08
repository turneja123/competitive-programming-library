//https://atcoder.jp/contests/abc208/tasks/abc208_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

set<long long> prod[20];
map<long long, long long> dp[20][3];

long long calc(long long n, int k) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int d = 1; d < 10; d++) {
        prod[0].insert(d);
        if (d < b[0]) {
            dp[0][0][d]++;
        } else if (d == b[0]) {
            dp[0][2][d]++;
        } else {
            dp[0][1][d]++;
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (long long j : prod[i - 1]) {
            for (int d = 0; d < 10; d++) {

                long long p = j * d;
                prod[i].insert(p);
                if (d < b[i]) {
                    dp[i][0][p] += dp[i - 1][0][j] + dp[i - 1][2][j];
                    dp[i][1][p] += dp[i - 1][1][j];
                } else if (d == b[i]) {
                    dp[i][0][p] += dp[i - 1][0][j];
                    dp[i][1][p] += dp[i - 1][1][j];
                    dp[i][2][p] += dp[i - 1][2][j];
                } else {
                    dp[i][1][p] += dp[i - 1][1][j] + dp[i - 1][2][j];
                    dp[i][0][p] += dp[i - 1][0][j];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < b.size(); i++) {
        for (long long j : prod[i]) {
            if (j > k) {
                continue;
            }
            ans += dp[i][0][j] + dp[i][2][j];
            if (i != b.size() - 1) {
                ans += dp[i][1][j];
            }
        }
    }
    return ans;
}

int main() {
    IOS;
    long long n, k;
    cin >> n >> k;
    cout << calc(n, k);
    return 0;
}
