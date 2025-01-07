//https://dmoj.ca/problem/mmm14d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1771561;

long long dp[N][3];
long long dp_next[N][3];

vector<int> digits[N];

int pw[N];
bool seen[N];

long long calc(long long n) {
    if (n == 0) {
        return 0;
    }
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    vector<int> masks;
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[d + 1][0] = 1;
        } else if (d == b[0]) {
            dp[d + 1][2] = 1;
        } else {
            dp[d + 1][1] = 1;
        }
        masks.push_back(d + 1);
    }
    long long ans = 0;
    for (int i = 1; i < b.size(); i++) {
        vector<int> next_masks;
        for (int j : masks) {
                for (int d = 0; d < 10; d++) {
                    int cur = 0;
                    for (int k = 0; k < 6; k++) {
                        if (k == 0) {
                            cur += min(d + 1, digits[j][k]);
                        } else {
                            if (digits[j][k - 1] != 0 && digits[j][k - 1] <= d + 1) {
                                if (digits[j][k] == 0) {
                                    cur += pw[k] * (d + 1);
                                } else {
                                    cur += pw[k] * min(d + 1, digits[j][k]);
                                }
                            } else {
                                cur += pw[k] * digits[j][k];
                            }
                        }
                    }
                    if (!seen[cur]) {
                        next_masks.push_back(cur);
                        seen[cur] = true;
                    }
                    if (d < b[i]) {
                        dp_next[cur][0] += dp[j][0] + dp[j][2];
                        dp_next[cur][1] += dp[j][1];
                    } else if (d == b[i]) {
                        dp_next[cur][0] += dp[j][0];
                        dp_next[cur][1] += dp[j][1];
                        dp_next[cur][2] += dp[j][2];
                    } else {
                        dp_next[cur][1] += dp[j][1] + dp[j][2];
                        dp_next[cur][0] += dp[j][0];
                    }
                }
            }
        masks = next_masks;
        for (int j : masks) {
            dp[j][0] = dp_next[j][0];
            dp[j][1] = dp_next[j][1];
            dp[j][2] = dp_next[j][2];
            dp_next[j][0] = 0;
            dp_next[j][1] = 0;
            dp_next[j][2] = 0;
            if (digits[j][5] != 0) {
                if (i < b.size() - 1) {
                    ans += dp[j][0] + dp[j][1] + dp[j][2];
                } else {
                    ans += dp[j][0] + dp[j][2];
                }
            }
            seen[j] = false;
        }
    }
    for (int j = 0; j < N; j++) {
        dp[j][0] = 0;
        dp[j][1] = 0;
        dp[j][2] = 0;
    }
    return ans;
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < 7; i++) {
        pw[i] = pw[i - 1] * 11;
    }
    for (int i = 1; i < N; i++) {
        int n = i;
        for (int j = 0; j < 6; j++) {
            digits[i].push_back(n % 11);
            n /= 11;
        }
    }
    long long l, r;
    cin >> l >> r;
    cout << calc(r) - calc(l - 1);
    return 0;
}
