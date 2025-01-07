//https://codeforces.com/contest/2036/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 70;

long long dp[N][3];
long long ways[N][N][3];
long long sum[N];

long long x(long long n) {
    long long m = n % 4;
    if (m == 0) {
        return n;
    } else if (m == 1) {
        return 1;
    } else if (m == 2) {
        return n + 1;
    } else {
        return 0;
    }
}

long long calc(long long n, int i, long long k) {
    if (n == 0) {
        return 0;
    }
    vector<int> dn, dk;
    long long nn = n, kk = k;
    while (nn > 0) {
        dn.push_back(nn % 2);
        nn /= 2;
    }
    while (kk > 0) {
        dk.push_back(kk % 2);
        kk /= 2;
    }
    while (dk.size() < i) {
        dk.push_back(0);
    }
    if (dn.size() <= dk.size()) {
        if (n >= k) {
            return x(n) ^ k;
        }
        return x(n);
    }
    reverse(dk.begin(), dk.end());
    reverse(dn.begin(), dn.end());
    dp[0][2] = 1;
    dp[0][0] = 1;
    ways[0][0][2] = 1;
    int m = dn.size() - dk.size();
    for (int i = 1; i < m; i++) {
        if (dn[i] == 0) {
            dp[i][0] += dp[i - 1][0];
            dp[i][1] += dp[i - 1][1];
            dp[i][2] += dp[i - 1][2];
            for (int k = 0; k < i; k++) {
                ways[i][k][0] += ways[i - 1][k][0];
                ways[i][k][1] += ways[i - 1][k][1];
                ways[i][k][2] += ways[i - 1][k][2];
            }

            dp[i][0] += dp[i - 1][0];
            dp[i][1] += dp[i - 1][1] + dp[i - 1][2];
            for (int k = 0; k < i; k++) {
                ways[i][k][0] += ways[i - 1][k][0];
                ways[i][k][1] += ways[i - 1][k][1] + ways[i - 1][k][2];
            }

            ways[i][i][0] += dp[i - 1][0];
            ways[i][i][1] += dp[i - 1][1] + dp[i - 1][2];
        } else {
            dp[i][0] += dp[i - 1][0] + dp[i - 1][2];
            dp[i][1] += dp[i - 1][1];
            for (int k = 0; k < i; k++) {
                ways[i][k][0] += ways[i - 1][k][0] + ways[i - 1][k][2];
                ways[i][k][1] += ways[i - 1][k][1];
            }

            dp[i][0] += dp[i - 1][0];
            dp[i][1] += dp[i - 1][1];
            dp[i][2] += dp[i - 1][2];
            for (int k = 0; k < i; k++) {
                ways[i][k][0] += ways[i - 1][k][0];
                ways[i][k][1] += ways[i - 1][k][1];
                ways[i][k][2] += ways[i - 1][k][2];
            }

            ways[i][i][0] += dp[i - 1][0];
            ways[i][i][1] += dp[i - 1][1];
            ways[i][i][2] += dp[i - 1][2];
        }
    }
    int tight = 2;
    for (int i = m; i < dn.size() && tight == 2; i++) {
        if (dn[i] > dk[i - m]) {
            tight = 0;
        } else if (dn[i] < dk[i - m]) {
            tight = 1;
        }
    }
    long long ct = (tight == 0 || tight == 2 ? dp[m - 1][0] + dp[m - 1][2] : dp[m - 1][0]);
    if (tight == 0 || tight == 2) {
        for (int j = 0; j < m; j++) {
            sum[j] += ways[m - 1][j][0] + ways[m - 1][j][2];
        }
    } else {
        for (int j = 0; j < m; j++) {
            sum[j] += ways[m - 1][j][0];
        }
    }
    long long ans = x(n);
    if (ct % 2 == 1) {
        ans ^= k;
    }
    for (int j = 0; j < m; j++) {
        int k = dn.size() - 1;
        if (sum[j] % 2 == 1) {
            int k = dn.size() - 1;
            ans ^= 1ll << (k - j);
        }
    }
    for (int i = 0; i < m; i++) {
        dp[i][0] = 0, dp[i][1] = 0, dp[i][2] = 0;
        sum[i] = 0;
        for (int j = 0; j < m; j++) {
            ways[i][j][0] = 0, ways[i][j][1] = 0, ways[i][j][2] = 0;
        }
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long l, r, i, k;
        cin >> l >> r >> i >> k;
        long long ans = calc(r, i, k) ^ calc(l - 1, i, k);
        cout << ans << endl;
    }
    return 0;
}
