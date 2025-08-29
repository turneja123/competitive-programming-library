//https://codeforces.com/contest/2129/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int INF = 1e9;
const ll M = 998244353;

int a[N];
int seen[N][N];
vector<vector<int>> dp[N][N];

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

vector<vector<int>> sentinel(1, vector<int>(1, 1));

const vector<vector<int>>& calc(int l, int r, int n) {
    int m = r - l + 1;
    if (l > r) {
        return sentinel;
    }
    if (seen[l][r]) {
        return dp[l][r];
    }
     vector<vector<int>> cur(m + 1, vector<int>(m + 1, 0));

    seen[l][r] = true;

    int L = l - 1, R = r + 1;
    for (int i = l; i <= r; i++) {
        const auto& ldp = calc(l, i - 1, n);
        const auto& rdp = calc(i + 1, r, n);
        int ln = ldp.size();
        int rn = rdp.size();

        int dl = i - L;
        int dr = R - i;
        if (L == 0) {
            dl = INF;
        }
        if (R == n + 1) {
            dr = INF;
        }
        int fl, fr;
        if (dl > dr) {
            fl = 0;
            fr = 1;
        } else {
            fl = 1;
            fr = 0;
        }
        if (L == 0) {
            fl = 0;
        }
        if (R == n + 1) {
            fr = 0;
        }
        /*for (int p = 0; p < ln; p++) {
            for (int q = 0; q < ln; q++) {
                for (int j = 0; j < rn; j++) {
                    for (int t = 0; t < rn; t++) {
                        if (a[i] == -1 || q + j == a[i]) {
                            cur[p + fl][t + fr] = (cur[p + fl][t + fr] + (ll)ldp[p][q] * rdp[j][t] % M * binomial(i - l + r - i, i - l)) % M;
                        }
                    }
                }
            }
        }*/
        if (a[i] == -1) {
            vector<int> sl(ln, 0), sr(rn, 0);
            for (int p = 0; p < ln; p++) {
                for (int q = 0; q < ln; q++) {
                    sl[p] = (sl[p] + ldp[p][q]) % M;
                }
            }
            for (int t = 0; t < rn; t++) {
                for (int j = 0; j < rn; j++) {
                    sr[t] = (sr[t] + rdp[j][t]) % M;
                }
            }
            for (int p = 0; p < ln; p++) {
                for (int t = 0; t < rn; t++) {
                    cur[p + fl][t + fr] = (cur[p + fl][t + fr] + (ll)sl[p] * binomial(i - l + r - i, i - l) % M * sr[t] % M) % M;
                }
            }
        } else {
            if (max(0, a[i] - (rn - 1)) <= min(ln - 1, a[i])) {
                for (int p = 0; p < ln; p++) {
                    for (int q = max(0, a[i] - (rn - 1)); q <= min(ln - 1, a[i]); q++) {
                        if (ldp[p][q] == 0) {
                            continue;
                        }
                        for (int t = 0; t < rn; t++) {
                            cur[p + fl][t + fr] = (cur[p + fl][t + fr] + (ll)ldp[p][q] * binomial(i - l + r - i, i - l) % M * rdp[a[i] - q][t] % M) % M;
                        }
                    }
                }
            }
        }
    }
    return dp[l][r] = cur;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        const auto&  d = calc(1, n, n);
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                ans = (ans + d[i][j]) % M;
                seen[i][j] = false;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
