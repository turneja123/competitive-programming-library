//https://www.codechef.com/problems/GCDEQMEX
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 998244353;

int a[N];
int freq[N];
int d[N];
long long pw[N];
long long ipw[N];
long long pw3[N];
long long ans[N];
long long dp[N];

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    pw[0] = 1, ipw[0] = 1, pw3[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
        pw3[i] = pw3[i - 1] * 3 % M;
        ipw[i] = ipw[i - 1] * 499122177 % M;
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            freq[a[i]]++;
            mx = max(mx, a[i]);
        }
        for (int i = 1; i <= mx; i++) {
            for (int j = i; j <= mx; j += i) {
                d[i] += freq[j];
            }
            dp[i] = pw[d[i]] - 1;
            for (int j = 1; j <= d[i]; j++) {
                ans[i] = (ans[i] + binomial(d[i], j) * ipw[j]) % M;
            }
        }
        for (int i = mx; i > 0; i--) {
            for (int j = 2 * i; j <= mx; j += i) {
                ans[i] = (ans[i] - ans[j] + M) % M;
                dp[i] = (dp[i] - dp[j] + M) % M;
            }
        }
        long long sum = 0, prod = 1;
        int pref = 0;
        for (int i = 1; i <= mx; i++) {
            long long p = 0;
            for (int j = 1; j <= d[i] - freq[i]; j++) {
                p = (p + binomial(d[i] - freq[i], j) * ipw[j]) % M;
            }
            for (int j = 2 * i; j <= mx; j += i) {
                p = (p - ans[j] + M) % M;
            }

            sum = (sum + prod * p % M * pw[d[i] - freq[i]] % M * pw[n - d[i] - pref]) % M;
            sum = (sum + prod * (pw[freq[i]] - 1) % M * pw3[d[i] - freq[i]] % M * pw[n - d[i] - pref]) % M;
            if (freq[i] == 0) {
                break;
            }
            prod = prod * (pw[freq[i]] - 1) % M;
            pref += freq[i];
        }
        cout << (sum - dp[1] + M) % M << endl;
        for (int i = 1; i <= mx; i++) {
            ans[i] = 0;
            dp[i] = 0;
            freq[i] = 0;
            d[i] = 0;
        }
    }

    return 0;
}
