//https://www.spoj.com/problems/PSTRING/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10005, M = 1005;
const int INF = 1e9;

int dp[N][M];

int prefix[M];
int trans[M][26];

int main() {
    //IOS;
    string a, s;
    while (cin >> a) {
        cin >> s;
        int n = a.size(), m = s.size();
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
            for (int c = 0; c < 26; c++) {
                char ch = 'a' + c;
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
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = INF;
            }
        }
        if (a[0] == s[0]) {
            dp[0][1] = 0;
            dp[0][0] = 1;
        } else {
            dp[0][0] = 0;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                if (trans[j][a[i] - 'a'] != m) {
                    dp[i][trans[j][a[i] - 'a']] = min(dp[i][trans[j][a[i] - 'a']], dp[i - 1][j]);
                }
            }
        }
        int ans = n;
        for (int j = 0; j < m; j++) {
            ans = min(ans, dp[n - 1][j]);
        }
        cout << ans << endl;
    }
    return 0;
}
