//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll dp[N][5][3];

//o
//+
//-
//-+
//+-

//o+, ++, +-+ skip
//o-, --, -+- skip

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < 5; j++) {
                for (int t = 0; t < 3; t++) {
                    dp[i][j][t] = 0;
                }
            }
        }
        dp[n][0][0] = 1;
        ll ans = 1;
        for (int i = n - 1; i >= 0; i--) {
            vector<char> add;
            if (s[i] == '?') {
                ans = ans * 3 % M;
                add = {'o', '-', '+'};
            } else if (s[i] == '0') {
                add = {'o'};
            } else if (s[i] == '-') {
                add = {'-'};
            } else {
                add = {'+'};
            }
            for (int j = 0; j < 5; j++) {
                for (int t = 0; t < 3; t++) {
                    for (char d : add) {
                        int t_nx = t;
                        if (t == 0 && j == 1 && d == 'o') {
                            t_nx = 2;
                        }
                        if (t == 0 && j == 2 && d == 'o') {
                            t_nx = 1;
                        }
                        if (t == 0 && (j == 1 || j == 3) && d == '+') {
                            t_nx = 2;
                        }
                        if (t == 0 && (j == 2 || j == 4) && d == '-') {
                            t_nx = 1;
                        }
                        int j_nx = 0;
                        if (t_nx == 0) {
                            if (j == 0) {
                                if (d == '+') {
                                    j_nx = 1;
                                }
                                if (d == '-') {
                                    j_nx = 2;
                                }
                            } else if (j == 1) {
                                if (d == '-') {
                                    j_nx = 3;
                                }
                            } else if (j == 2) {
                                if (d == '+') {
                                    j_nx = 4;
                                }
                            } else if (j == 3) {
                                if (d == '-') {
                                    j_nx = 0;
                                }
                                if (d == 'o') {
                                    j_nx = 1;
                                }
                            } else {
                                if (d == '+') {
                                    j_nx = 0;
                                } else if (d == 'o') {
                                    j_nx = 2;
                                }
                            }
                        }
                        dp[i][j_nx][t_nx] = (dp[i][j_nx][t_nx] + dp[i + 1][j][t]) % M;
                    }
                }
            }
        }
        ll a = 0, b = 0, c = 0;
        for (int j = 0; j < 5; j++) {
            a = (a + dp[0][j][2]) % M;
            b = (b + dp[0][j][1]) % M;
        }
        a = (a + dp[0][1][0]) % M;
        b = (b + dp[0][2][0]) % M;
        c = (ans - a - b + 2 * M) % M;
        cout << a << " " << b << " " << c << endl;
    }

    return 0;
}
