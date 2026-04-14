//https://www.spoj.com/problems/NUMTSN/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;

int dp[51][36][36][2][2];

void init() {
    int mid = 18;
    dp[0][mid][mid][1][1] = 1;
    for (int i = 1; i <= 50; i++) {
        int l = max(0, mid - i), r = min(35, mid + i);
        for (int j = l; j <= r; j++) {
            for (int k = l; k <= r; k++) {
                for (int f = 0; f < 2; f++) {
                    for (int t = 0; t < 2; t++) {
                        for (int d = 0; d < 10; d++) {
                            int t_nx = t;
                            int j_nx = j;
                            int k_nx = k;
                            int f_nx = f;
                            if (t_nx == 0 && d == 0) {
                            } else {
                                t_nx = 1;
                                j_nx += (d == 3) - (d == 6);
                                k_nx += (d == 3) - (d == 9);
                                f_nx |= d == 3;
                            }
                            if (j_nx >= 0 && j_nx < 36 && k_nx >= 0 && k_nx < 36) {
                                dp[i][j][k][f][t] += dp[i - 1][j_nx][k_nx][f_nx][t_nx];
                                if (dp[i][j][k][f][t] >= M) {
                                    dp[i][j][k][f][t] -= M;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int calc(string &s) {
    int n = s.size();

    int mid = 18;

    int j = mid, k = mid, f = 0, t = 0;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - '0';
        for (int d = 0; d < c; d++) {
            int t_nx = t;
            int j_nx = j;
            int k_nx = k;
            int f_nx = f;
            if (t_nx == 0 && d == 0) {
            } else {
                t_nx = 1;
                j_nx += (d == 3) - (d == 6);
                k_nx += (d == 3) - (d == 9);
                f_nx |= d == 3;
            }
            if (j_nx >= 0 && j_nx < 36 && k_nx >= 0 && k_nx < 36) {
                ans += dp[n - i - 1][j_nx][k_nx][f_nx][t_nx];
                if (ans >= M) {
                    ans -= M;
                }
            }
        }
        if (t == 0 && c == 0) {
            continue;
        }
        t = 1;
        j += (c == 3) - (c == 6);
        k += (c == 3) - (c == 9);
        f |= c == 3;
    }
    if (j == mid && k == mid && f == 1 && t == 1) {
        ans++;
    }
    return ans % M;
}


int chk(string a) {
    int f[10] = {};
    for (int i = 0; i < a.size(); i++) {
        f[a[i] - '0']++;
    }
    return f[3] && f[3] == f[6] && f[3] == f[9];
}

int main() {
    IOS;
    init();
    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;
        cout << (calc(b) - calc(a) + chk(a) + M) % M << endl;
    }
    return 0;
}
