//https://www.codechef.com/problems/XORSPATH
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 20;
const int N = (1 << K);
const long long M = 998244353;

int a[N];
int freq[N];
bool flip[K];
int skip[K];
long long dp[N];
long long sos[N];

vector<int> masks[K + 1];

long long inv[N];
long long fact[N];
long long factinv[N];
long long pref[N];

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1, pref[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
        pref[i] = (pref[i - 1] + factinv[i]) % M;
        masks[__builtin_popcount(i)].push_back(i);
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int k = log2(n) + 1;
        k = min(k, K);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int x = a[0] ^ a[n - 1];
        for (int j = 0; j < k; j++) {
            int c1 = (1 << j) & x;
            int c2 = (1 << j) & a[0];
            if (c1) {
                skip[j] = 0;
                if (c2) {
                    flip[j] = 1;
                } else {
                    flip[j] = 0;
                }
            } else {
                if (c2) {
                    skip[j] = 1;
                } else {
                    skip[j] = 2;
                }
            }
        }
        for (int i = 1; i < n - 1; i++) {
            int good = 1, mask = 0;
            for (int j = 0; j < k; j++) {
                int c = (1 << j) & a[i];
                if (skip[j] != 0) {
                    if (skip[j] == 1 && !c) {
                        good = 0;
                    }
                    if (skip[j] == 2 && c) {
                        good = 0;
                    }
                } else {
                    if (flip[j] == 0 && c) {
                        mask += 1 << j;
                    }
                    if (flip[j] == 1 && !c) {
                        mask += 1 << j;
                    }
                }
            }
            if (good) {
                freq[mask]++;
            }
        }
        dp[0] = fact[freq[0]] * pref[freq[0]] % M - 1;
        long long ans = 1 + dp[0];
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < 1 << k; j++) {
                sos[j] = dp[j];
            }
            for (int z = 0; z < k; z++) {
                for (int j = 0; j < 1 << k; j++) {
                    int c = j & (1 << z);
                    if (c) {
                        sos[j] = (sos[j] + sos[j ^ (1 << z)]) % M;
                    }
                }
            }
            for (int j : masks[i]) {
                dp[j] = (sos[j] + 1) * (fact[freq[j]] * pref[freq[j]] % M - 1) % M;
                ans = (ans + dp[j]) % M;
            }
        }
        cout << x << " " << ans << endl;
        for (int i = 0; i < 1 << k; i++) {
            dp[i] = 0;
            sos[i] = 0;
            freq[i] = 0;
        }


    }
    return 0;
}
