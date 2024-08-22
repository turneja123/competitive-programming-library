//https://atcoder.jp/contests/abc235/tasks/abc235_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10005;
const int K = 1024;
const long long M = 998244353;

pair<long long, long long> dp[N][K][3];
string s;
int a[N];
int pos[10];

int main() {
    IOS;
    for (int i = 0; i < 10; i++) {
        pos[i] = -1;
    }
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        int d;
        cin >> d;
        pos[d] = i;
    }
    for (int d = 1; d < 10; d++) {
        int mask = 0;
        if (pos[d] != -1) {
            mask += 1 << pos[d];
        }
        if (a[0] > d) {
            dp[0][mask][0].first = (dp[0][mask][0].first + 1) % M;
            dp[0][mask][0].second = (dp[0][mask][0].second + d) % M;
        } else if (a[0] == d) {
            dp[0][mask][2].first = (dp[0][mask][2].first + 1) % M;
            dp[0][mask][2].second = (dp[0][mask][2].second + d) % M;
        } else {
            dp[0][mask][1].first = (dp[0][mask][1].first + 1) % M;
            dp[0][mask][1].second = (dp[0][mask][1].second + d) % M;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int d = 0; d < 10; d++) {
            for (int mask = 0; mask < 1 << c; mask++) {
                if (pos[d] != -1) {
                    int bit = 1 << pos[d], x = mask & bit;
                    if (x == 0) {
                        continue;
                    }
                }
                if (a[i] > d) {
                    dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][mask][0].first + dp[i - 1][mask][2].first) % M;
                    dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][mask][1].first) % M;

                    dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][mask][0].second * 10 + dp[i - 1][mask][0].first * d) + (dp[i - 1][mask][2].second * 10 + dp[i - 1][mask][2].first * d)) % M;
                    dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][mask][1].second * 10 + dp[i - 1][mask][1].first * d)) % M;

                    if (pos[d] != -1) {
                        int sub = mask ^ (1 << pos[d]);
                        dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][sub][0].first + dp[i - 1][sub][2].first) % M;
                        dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][sub][1].first) % M;

                        dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][sub][0].second * 10 + dp[i - 1][sub][0].first * d) + (dp[i - 1][sub][2].second * 10 + dp[i - 1][sub][2].first * d)) % M;
                        dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][sub][1].second * 10 + dp[i - 1][sub][1].first * d)) % M;
                    }
                } else if (a[i] == d) {
                    dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][mask][0].first) % M;
                    dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][mask][1].first) % M;
                    dp[i][mask][2].first = (dp[i][mask][2].first + dp[i - 1][mask][2].first) % M;

                    dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][mask][0].second * 10 + dp[i - 1][mask][0].first * d)) % M;
                    dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][mask][1].second * 10 + dp[i - 1][mask][1].first * d)) % M;
                    dp[i][mask][2].second = (dp[i][mask][2].second + (dp[i - 1][mask][2].second * 10 + dp[i - 1][mask][2].first * d)) % M;

                    if (pos[d] != -1) {
                        int sub = mask ^ (1 << pos[d]);
                        dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][sub][0].first) % M;
                        dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][sub][1].first) % M;
                        dp[i][mask][2].first = (dp[i][mask][2].first + dp[i - 1][sub][2].first) % M;

                        dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][sub][0].second * 10 + dp[i - 1][sub][0].first * d)) % M;
                        dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][sub][1].second * 10 + dp[i - 1][sub][1].first * d)) % M;
                        dp[i][mask][2].second = (dp[i][mask][2].second + (dp[i - 1][sub][2].second * 10 + dp[i - 1][sub][2].first * d)) % M;
                    }

                } else {
                    dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][mask][1].first + dp[i - 1][mask][2].first) % M;
                    dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][mask][0].first) % M;

                    dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][mask][1].second * 10 + dp[i - 1][mask][1].first * d) + (dp[i - 1][mask][2].second * 10 + dp[i - 1][mask][2].first * d)) % M;
                    dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][mask][0].second * 10 + dp[i - 1][mask][0].first * d)) % M;

                    if (pos[d] != -1) {
                        int sub = mask ^ (1 << pos[d]);
                        dp[i][mask][1].first = (dp[i][mask][1].first + dp[i - 1][sub][1].first + dp[i - 1][sub][2].first) % M;
                        dp[i][mask][0].first = (dp[i][mask][0].first + dp[i - 1][sub][0].first) % M;

                        dp[i][mask][1].second = (dp[i][mask][1].second + (dp[i - 1][sub][1].second * 10 + dp[i - 1][sub][1].first * d) + (dp[i - 1][sub][2].second * 10 + dp[i - 1][sub][2].first * d)) % M;
                        dp[i][mask][0].second = (dp[i][mask][0].second + (dp[i - 1][sub][0].second * 10 + dp[i - 1][sub][0].first * d)) % M;
                    }
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + dp[i][(1 << c) - 1][0].second + dp[i][(1 << c) - 1][2].second) % M;
        if (i != n - 1) {
            ans = (ans + dp[i][(1 << c) - 1][1].second) % M;
        }
    }
    cout << ans;
    return 0;
}
