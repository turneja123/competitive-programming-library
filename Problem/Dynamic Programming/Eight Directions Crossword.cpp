//https://www.spoj.com/problems/EIGHT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int row[N][N];
int col[N][N];
int diag[N][N];
int adiag[N][N];

string a[N];


ll calc(string &a, string &b) {
    int n = a.size(), m = b.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] += dp[i - 1][j];
            if (j != 0 && a[i - 1] == b[j - 1]) {
                dp[i][j] += dp[i - 1][j - 1];
            }
        }
    }
    return dp[n][m];
}

int main() {
    IOS;
    int n;
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!row[i][j]) {
                int x = i, y = j;
                string b = "";
                while (x < n && y < n) {
                    row[x][y] = 1;
                    b += a[x][y];
                    x++;
                }
                ans += calc(b, s);
                reverse(b.begin(), b.end());
                ans += calc(b, s);
            }
            if (!col[i][j]) {
                int x = i, y = j;
                string b = "";
                while (x < n && y < n) {
                    col[x][y] = 1;
                    b += a[x][y];
                    y++;
                }
                ans += calc(b, s);
                reverse(b.begin(), b.end());
                ans += calc(b, s);
            }
            if (!diag[i][j]) {
                int x = i, y = j;
                string b = "";
                while (x < n && y < n) {
                    diag[x][y] = 1;
                    b += a[x][y];
                    x++, y++;
                }
                ans += calc(b, s);
                reverse(b.begin(), b.end());
                ans += calc(b, s);
            }
            if (!adiag[i][j]) {
                int x = i, y = j;
                string b = "";
                while (x < n && y >= 0) {
                    adiag[x][y] = 1;
                    b += a[x][y];
                    x++, y--;
                }
                ans += calc(b, s);
                reverse(b.begin(), b.end());
                ans += calc(b, s);
            }
        }
    }
    cout << ans;

    return 0;
}
