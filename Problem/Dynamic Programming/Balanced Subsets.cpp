//https://codeforces.com/contest/2279/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 2e5 + 5;
const int M = 998244353;
const int INF = 1e9;

int dp[N][16];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (n == 2) {
            cout << 3 << endl;
            continue;
        }
        if (n == 3) {
            int ans = 6;
            if (a[2] - a[0] <= 3) {
                ans++;
            }
            cout << ans << endl;
            continue;
        }

        int ans = (n + (ll)n * (n - 1) / 2) % M;
        a.push_back(INF);
        a.push_back(INF + 5);
        a.push_back(INF + 10);
        n += 3;

        for (int cur = 0; cur < 16; cur++) {
            int ok = 1;
            if (cur >= 8) {
                int ct = 0;
                if ((cur & 4) > 0 && a[1] - a[0] <= 3) {
                    ct++;
                }
                if ((cur & 2) > 0 && a[2] - a[0] <= 3) {
                    ct++;
                }
                if ((cur & 1) > 0 && a[3] - a[0] <= 3) {
                    ct++;
                }
                if (ct != 2) {
                    ok = 0;
                }
            }
            dp[3][cur] = ok;

            if (ok && cur >= 8 && __builtin_popcount(cur & 7) == 2) {
                ans = (ans + 1) % M;
            }
        }


        for (int i = 4; i < n; i++) {
            for (int mask = 0; mask < 16; mask++) {
                dp[i][mask] = 0;
            }
            for (int mask = 0; mask < 16; mask++) {

                int cur = mask;
                if (cur >= 8) {
                    cur -= 8;
                }
                cur *= 2;
                int ok = 1;
                if (cur >= 8) {
                    int ct = 0;
                    if ((cur & 4) > 0 && a[i - 2] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if ((cur & 2) > 0 && a[i - 1] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if ((cur & 1) > 0 && a[i] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if (ct != 2) {
                        ok = 0;
                    }
                }
                if (ok) {
                    dp[i][cur] = (dp[i][cur] + dp[i - 1][mask]) % M;
                    if (cur >= 8) {
                        ans = (ans + dp[i - 1][mask]) % M;
                    }
                }

                cur++;
                ok = 1;
                if (cur >= 8) {
                    int ct = 0;
                    if ((cur & 4) > 0 && a[i - 2] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if ((cur & 2) > 0 && a[i - 1] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if ((cur & 1) > 0 && a[i] - a[i - 3] <= 3) {
                        ct++;
                    }
                    if (ct != 2) {
                        ok = 0;
                    }
                }
                if (ok) {
                    dp[i][cur] = (dp[i][cur] + dp[i - 1][mask]) % M;
                    if (cur >= 8  && __builtin_popcount(cur & 7) == 2) {
                        ans = (ans + dp[i - 1][mask]) % M;
                    }
                }

            }
        }
        cout << ans << endl;


    }

    return 0;
}
