//https://www.spoj.com/problems/SANVI/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

const int D = 10;

long long a[3];
long long dp[1 << (2 * (D - 1))][37][2]; // maska base 4(0 - nema, 1 - jedan, 2 - dva, 3 - vise od 2 (jedan od izuzetaka, max 5 takvih)), suma counts (ako je manje od 18 znaci ima vise prostih), tight
long long dp_next[1 << (2 * (D - 1))][37][2];
bool is_prime[D];
int popcount[1 << (2 * (D - 1))];
int popcount3[1 << (2 * (D - 1))];
bool bad[1 << (2 * (D - 1))];
int pw[D];
int sum[1 << (2 * (D - 1))];
vector<int> pos[1 << (2 * (D - 1))];

int ct = 0;

long long calc(long long n, long long k, long long m) {
    long long ans = 0;
    for (int d = 1; d < 10; d++) {
        dp[pw[d - 1]][17][0] = 0;
        dp[pw[d - 1]][17][1] = 0;
        dp[pw[d - 1]][19][0] = 0;
        dp[pw[d - 1]][19][1] = 0;
        int c = n % 10;
        if (c >= d) {
            if (is_prime[d]) {
                dp[pw[d - 1]][17][0] = 1;
                if (k >= 1) {
                    ans++;
                }
            } else {
                dp[pw[d - 1]][19][0] = 1;
                if (k >= 1) {
                    ans++;
                }
            }
        } else {
            if (is_prime[d]) {
                dp[pw[d - 1]][17][1] = 1;
                if (k >= 1 && n >= d) {
                    ans++;
                }
            } else {
                dp[pw[d - 1]][19][1] = 1;
                if (k >= 1 && n >= d) {
                    ans++;
                }
            }
        }
    }
    int bits = 1 << (2 * (D - 1)), digs = 2;
    n /= 10;
    while (n > 0) {
        int c = n % 10;
        for (int mask = 1; mask < bits; mask++) {
            if (bad[mask] || popcount3[mask] > m || popcount[mask] > digs) {
                continue;
            }
            for (int d = 1; d < 10; d++) {
                if (pos[mask][d - 1] == 0) {
                    continue;
                }
                for (int j = max(0, sum[mask] - 1); j <= min(36, sum[mask] + 1); j++) {
                    if (pos[mask][d - 1] != 3) {
                        if (is_prime[d] && j == 36) {
                            continue;
                        }
                        if (!is_prime[d] && j == 0) {
                            continue;
                        }
                    }
                   // ct++;
                    int dj = ((is_prime[d]) ? 1 : -1);
                    if (pos[mask][d - 1] == 3) {
                        dj = 0;
                    }
                    int dm = ((pos[mask][d - 1] == 3) ? 0 : pw[d - 1]);
                    int prev_mask = mask - dm, prev_j = j + dj;
                    if (c > d) {
                        dp_next[mask][j][0] += dp[prev_mask][prev_j][0] + dp[prev_mask][prev_j][1];
                        if (pos[mask][d - 1] == 3) {
                            dp_next[mask][j][0] += dp[prev_mask - pw[d - 1]][prev_j][0] + dp[prev_mask - pw[d - 1]][prev_j][1];
                        }
                        if (abs(18 - j) <= k) {
                            ans += dp[prev_mask][prev_j][0] + dp[prev_mask][prev_j][1];
                            if (pos[mask][d - 1] == 3) {
                                ans += dp[prev_mask - pw[d - 1]][prev_j][0] + dp[prev_mask - pw[d - 1]][prev_j][1];
                            }
                        }
                    } else if (c == d) {
                        dp_next[mask][j][0] += dp[prev_mask][prev_j][0];
                        dp_next[mask][j][1] += dp[prev_mask][prev_j][1];
                        if (pos[mask][d - 1] == 3) {
                            dp_next[mask][j][0] += dp[prev_mask - pw[d - 1]][prev_j][0];
                            dp_next[mask][j][1] += dp[prev_mask - pw[d - 1]][prev_j][1];
                        }
                        if (abs(18 - j) <= k) {
                            ans += dp[prev_mask][prev_j][0];
                            if (pos[mask][d - 1] == 3) {
                                ans += dp[prev_mask - pw[d - 1]][prev_j][0];
                            }
                            if (n > 9) {
                                ans += dp[prev_mask][prev_j][1];
                                if (pos[mask][d - 1] == 3) {
                                    ans += dp[prev_mask - pw[d - 1]][prev_j][1];
                                }
                            }
                        }
                    } else {
                        dp_next[mask][j][1] += dp[prev_mask][prev_j][0] + dp[prev_mask][prev_j][1];
                        if (pos[mask][d - 1] == 3) {
                            dp_next[mask][j][1] += dp[prev_mask - pw[d - 1]][prev_j][0] + dp[prev_mask - pw[d - 1]][prev_j][1];
                        }
                        if (abs(18 - j) <= k && n > 9) {
                            ans += dp[prev_mask][prev_j][0] + dp[prev_mask][prev_j][1];
                            if (pos[mask][d - 1] == 3) {
                                ans += dp[prev_mask - pw[d - 1]][prev_j][0] + dp[prev_mask - pw[d - 1]][prev_j][1];
                            }
                        }
                    }
                }
            }
        }
        for (int mask = 1; mask < bits; mask++) {
            if (bad[mask] || popcount3[mask] > m) {
                continue;
            }
            for (int j = 0; j < 37; j++) {
                dp[mask][j][0] = dp_next[mask][j][0];
                dp[mask][j][1] = dp_next[mask][j][1];
                dp_next[mask][j][0] = 0;
                dp_next[mask][j][1] = 0;
            }
        }
        n /= 10;
        digs++;
    }
    return ans;
}

long long brute(long long n, long long k, long long m) {
    long long ct = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> freq(10, 0);
        int t = i;
        while (t > 0) {
            freq[t % 10]++;
            t /= 10;
        }
        if (freq[0] > 0) {
            continue;
        }
        if (freq[2] > 2 || freq[3] > 2 || freq[5] > 2 || freq[7] > 2) {
            continue;
        }
        int mm = 0;
        for (int f : freq) {
            if (f == 3) {
                mm++;
            }
        }
        if (mm > m) {
            continue;
        }
        int l = 0, r = 0;
        for (int j = 1; j < 10; j++) {
            if (is_prime[j]) {
                l += min(freq[j], 2);
            } else {
                r += min(freq[j], 2);
            }
        }
        if (abs(l - r) > k) {
            continue;
        }
        ct++;
    }
    return ct;
}

int main() {
    //IOS;
    pw[0] = 1;
    for (int i = 1; i < D; i++) {
        pw[i] = pw[i - 1] * 4;
    }
    int bits = 1 << (2 * (D - 1));
    is_prime[2] = true, is_prime[3] = true, is_prime[5] = true, is_prime[7] = true;
    for (int i = 1; i < bits; i++) {
        pos[i].resize(D - 1);
        int t = i, j = 0;
        sum[i] = 18;
        while (t > 0) {
            int m = t % 4;
            popcount[i] += m;
            if (m == 3) {
                popcount3[i]++;
                if (is_prime[j + 1]) {
                    bad[i] = true;
                }
            }
            int add = ((is_prime[j + 1]) ? -1 : 1);
            if (m == 1) {
                sum[i] += add;
            }
            if (m == 2 || m == 3) {
                sum[i] += 2 * add;
            }
            t /= 4;
            pos[i][j] = m;
            j++;
        }
    }
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        for(int i = 0; i < 3; i++) {
            iss >> a[i];
        }
        long long n = a[0], k = a[1], m = a[2];
        if (n == 1e18) {
            n--;
        }
        long long ans = calc(n, k, m);
        cout << ans % M << endl;
        //cout << brute(n, k, m) << endl;
    }

    return 0;
}
