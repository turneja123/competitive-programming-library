//https://codeforces.com/contest/2176/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int W = 6;

const long long M = 998244353;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

ll w[2 * W + 1];
bool is_prime[N];
int freq[W + 1][N];
ll dp[W + 1][W + 1];
int ncr[W + 1][W + 1];

vector<int> divs[N];

int main() {
    IOS;
    for (int i = 0; i <= W; i++) {
        ncr[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
        }
    }
    for (int i = 2; i < N; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) {
            divs[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                is_prime[j] = 0;
                divs[j].push_back(i);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<pair<int, int>> v;
        int last = a[0], ct = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] != last) {
                v.push_back({last, ct});
                last = a[i];
                ct = 1;
            } else {
                ct++;
            }
        }
        v.push_back({last, ct});
        for (int i = 0; i < v.size(); i++) {
            auto [n, ct] = v[i];
            int m = divs[n].size();
            w[m] = (w[m] + (ll)ct * (ct - 1) / 2) % M;
            for (int i = 0; i < 1 << m; i++) {
                int prod = 1;
                for (int j = 0; j < m; j++) {
                    int c = (1 << j) & i;
                    if (c) {
                        prod *= divs[n][j];
                    }
                }
                for (int k = 0; k <= W; k++) {
                    dp[k][__builtin_popcount(i)] += freq[k][prod];
                }
            }

            for (int k = 0; k <= W; k++) {
                for (int i = k; i >= 0; i--) {
                    for (int j = i + 1; j <= k; j++) {
                        dp[k][i] -= dp[k][j] * ncr[j][i];
                    }
                    w[m + k - i] = (w[m + k - i] + dp[k][i] * ct) % M;
                }
            }

            for (int i = 0; i < 1 << m; i++) {
                int prod = 1;
                for (int j = 0; j < m; j++) {
                    int c = (1 << j) & i;
                    if (c) {
                        prod *= divs[n][j];
                    }
                }
                freq[m][prod] += ct;
            }
            for (int i = 0; i <= W; i++) {
                for (int j = 0; j <= W; j++) {
                    dp[i][j] = 0;
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i <= 2 * W; i++) {
            ans = (ans + modPow(i, k) * w[i]) % M;
            w[i] = 0;
        }
        cout << ans << endl;
        for (int i = 0; i <= W; i++) {
            for (int j = 0; j <= n; j++) {
                freq[i][j] = 0;
            }
        }
    }

    return 0;
}
