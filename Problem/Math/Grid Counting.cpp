//https://codeforces.com/contest/2150/problem/B
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
int have[N];
long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
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
        int n, s = 0;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            have[i] = max(0, n - (i - 1) * 2);
            s += a[i];
        }
        ll ans = 1;
        if (s != n) {
            ans = 0;
        }
        int used = 0;
        for (int i = n; i >= 1; i--) {
            if (a[i] > have[i] - used) {
                ans = 0;
            }
            if (ans == 0) {
                break;
            }
            ans = ans * binomial(have[i] - used, a[i]) % M;
            used += a[i];
        }
        cout << ans << endl;
    }


    return 0;
}
