//https://atcoder.jp/contests/abc295/tasks/abc295_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 20;

int prefix[N];
int trans[N][10];
long long dp[N][N][N][3];

long long calc(string n, int m) {
    if (n == "0") {
        return 0;
    }
    for (int d = 1; d < 10; d++) {
        int tight;
        if (d < n[0] - '0') {
            tight = 0;
        } else if (d == n[0] - '0') {
            tight = 2;
        } else {
            tight = 1;
        }
        int k = trans[0][d];
        int j = (k == m);
        dp[0][j][k][tight]++;
    }

    for (int i = 1; i < n.size(); i++) {
        for (int j = 0; j <= n.size(); j++) {
            for (int k = 0; k <= m; k++) {
                for (int d = 0; d < 10; d++) {
                    int k_n = trans[k][d];
                    int j_n = j;
                    if (k_n == m) {
                        j_n++;
                    }
                    if (d < n[i] - '0') {
                        dp[i][j_n][k_n][0] += dp[i - 1][j][k][0] + dp[i - 1][j][k][2];
                        dp[i][j_n][k_n][1] += dp[i - 1][j][k][1];
                    } else if (d == n[i] - '0') {
                        dp[i][j_n][k_n][0] += dp[i - 1][j][k][0];
                        dp[i][j_n][k_n][1] += dp[i - 1][j][k][1];
                        dp[i][j_n][k_n][2] += dp[i - 1][j][k][2];
                    } else {
                        dp[i][j_n][k_n][0] += dp[i - 1][j][k][0];
                        dp[i][j_n][k_n][1] += dp[i - 1][j][k][1] + dp[i - 1][j][k][2];
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n.size(); i++) {
        for (int j = 0; j <= n.size(); j++) {
            for (int k = 0; k <= m; k++) {
                ans += (dp[i][j][k][0] + dp[i][j][k][2]) * j;
                if (i != n.size() - 1) {
                    ans += dp[i][j][k][1] * j;
                }
                dp[i][j][k][0] = 0;
                dp[i][j][k][1] = 0;
                dp[i][j][k][2] = 0;
            }
        }
    }
    return ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s; long long l, r;
        cin >> s >> l >> r;
        int m = s.size();
        int k = 0;
        for (int i = 1; i < m; i++) {
            while (k > 0 && s[k] != s[i]) {
                k = prefix[k - 1];
            }
            if (s[k] == s[i]) {
                k++;
            }
            prefix[i] = k;
        }
        for (int i = 0; i <= m; i++) {
            for (int c = 0; c < 10; c++) {
                char ch = '0' + c;
                if (i < m && ch == s[i]) {
                    trans[i][c] = i + 1;
                } else {
                    if (i == 0) {
                        trans[i][c] = 0;
                    } else {
                        trans[i][c] = trans[prefix[i - 1]][c];
                    }
                }
            }
        }
        long long ans = calc(to_string(r), m) - calc(to_string(l - 1), m);
        cout << ans << endl;
    }

    return 0;
}
