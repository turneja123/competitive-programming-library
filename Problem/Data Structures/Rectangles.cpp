//https://codeforces.com/contest/2159/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> a(n, vector<char>(m));
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                a[i][j] = s[j];
            }
        }
        bool flip = 0;
        if (n > m) {
            flip = 1;
            vector<vector<char>> a_t(m, vector<char>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    a_t[j][i] = a[i][j];
                }
            }
            a = a_t;
            swap(n, m);
        }
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, INF)));
        vector<vector<int>> ans(n, vector<int>(m, INF));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int l = -1;
                for (int r = 0; r < m; r++) {
                    if (a[i][r] == '1' && a[j][r] == '1') {
                        if (l != -1) {
                            int dim = (j - i + 1) * (r - l + 1);
                            for (int z = l; z <= r; z++) {
                                dp[z][i][j] = min(dp[z][i][j], dim);
                            }
                        }
                        l = r;
                    }
                }
            }
        }
        for (int z = 0; z < m; z++) {
            for (int i = n - 1; i >= 0; i--) {
                for (int j = 0; j + i < n; j++) {
                    dp[z][j][j + i] = min({dp[z][j][j + i], (j == 0 ? INF : dp[z][j - 1][j + i]), (j + i == n - 1 ? INF : dp[z][j][j + i + 1])});
                    if (i == 0) {
                        ans[j][z] = min(ans[j][z], dp[z][j][j]);
                    }
                }
            }
        }
        if (flip) {
            vector<vector<int>> ans_t(m, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    ans_t[j][i] = ans[i][j];
                }
            }
            ans = ans_t;
            swap(n, m);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << (ans[i][j] == INF ? 0 : ans[i][j]) << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
