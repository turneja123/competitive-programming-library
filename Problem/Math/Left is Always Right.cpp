//https://codeforces.com/contest/2161/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 1e5 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    if (k > n || n < 0 || k < 0) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int freq[N][2];
int state[N];

int ct[4];

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
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        for (int i = 2; i < n; i++) {
            if (s[i] == '0') {
                freq[i % (k - 1)][0]++;
            }
            if (s[i] == '1') {
                freq[i % (k - 1)][1]++;
            }
        }
        int bad = 0;
        for (int i = 0; i < k - 1; i++) {
            if (!freq[i][0] && !freq[i][1]) {
                state[i] = 0;
            }
            if (freq[i][0] && !freq[i][1]) {
                state[i] = 1;
            }
            if (!freq[i][0] && freq[i][1]) {
                state[i] = 2;
            }
            if (freq[i][0] && freq[i][1]) {
                state[i] = 3;
                bad++;
            }
            ct[state[i]]++;
        }

        auto ok = [&](int i, int v) -> bool {
            if (s[i] == '?') {
                return 1;
            }
            return s[i] - '0' == v;
        };
        int ok10 = 1, ok01 = 1;
        ll ans = 0;
        for (int i = 1; i + k - 1 <= n; i++) {
            if (!bad) {
                if (i + k - 1 == n) {
                    int f[3] = {};
                    for (int j = i; j < n; j++) {
                        if (s[j] == '?') {
                            f[0]++;
                        }
                        if (s[j] == '0') {
                            f[1]++;
                        }
                        if (s[j] == '1') {
                            f[2]++;
                        }
                    }
                    if (ok(i - 1, 1) && ok10) {
                        for (int j = max(k / 2, f[2]); j <= k; j++) {
                            ans += binomial(f[0], j - f[2]);
                        }
                    }
                    if (ok(i - 1, 0) && ok01) {
                        for (int j = max(k / 2, f[1]); j <= k; j++) {
                            ans += binomial(f[0], j - f[1]);
                        }
                    }
                } else {
                    int j = i % (k - 1);
                    if ((ok(i - 1, 1) && ok(i, 0) && ok10) && (state[j] == 1 || state[j] == 0)) {
                        ct[state[j]]--;
                        int need0 = k / 2 - ct[1] - 1;
                        int need1 = k / 2 - ct[2];
                        if (need0 >= 0 && need1 >= 0) {
                            ans += binomial(ct[0], need0);
                        }
                        ct[state[j]]++;
                    }
                    if ((ok(i - 1, 0) && ok(i, 1) && ok01) && (state[j] == 2 || state[j] == 0)) {
                        ct[state[j]]--;
                        int need0 = k / 2 - ct[1];
                        int need1 = k / 2 - ct[2] - 1;
                        if (need0 >= 0 && need1 >= 0) {
                            ans += binomial(ct[0], need0);
                        }
                        ct[state[j]]++;
                    }
                }
            }
            if (i + 1 < n) {
                int j = (i + 1) % (k - 1);
                ct[state[j]]--;
                if (state[j] == 3) {
                    bad--;
                }
                if (s[i + 1] == '0') {
                    freq[j][0]--;
                }
                if (s[i + 1] == '1') {
                    freq[j][1]--;
                }

                if (!freq[j][0] && !freq[j][1]) {
                    state[j] = 0;
                }
                if (freq[j][0] && !freq[j][1]) {
                    state[j] = 1;
                }
                if (!freq[j][0] && freq[j][1]) {
                    state[j] = 2;
                }
                if (freq[j][0] && freq[j][1]) {
                    state[j] = 3;
                    bad++;
                }
                ct[state[j]]++;
            }


            ok10 &= ok(i - 1, 1);
            ok01 &= ok(i - 1, 0);
            ans %= M;
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            state[i] = 0;
            freq[i][0] = 0, freq[i][1] = 0;
        }
        for (int i = 0; i < 4; i++) {
            ct[i] = 0;
        }
    }
    return 0;
}
