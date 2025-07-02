//https://ocpc2025s.eolymp.space/en/compete/mdpvbmkn7129t7jclok5kktmig/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;
const long long M = 998244353;


long long inv[N];
long long fact[N];
long long factinv[N];


long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

long long stars(long long n, long long k) {
    return binomial(n + k - 1, n);
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int a, e, i, o;
    cin >> a >> e >> i >> o;
    int n = a + e + i + o;
    if (a == n || e == n || i == n || o == n) {
        cout << 1;
        return 0;
    }
    long long ans = 0;

    if (e > 0) {
        ans = fact[n - 1] * factinv[a] % M * factinv[e - 1] % M * factinv[i] % M * factinv[o] % M;
        cout << ans;
    } else {
        if (o > 0) {
            if (a < i) {
                swap(a, i);
            }
            for (int j = 1; j <= min(a, o + 1); j++) {
                long long add = binomial(o + 1, j) * binomial(a - 1, j - 1) % M;
                if (i > 0) {
                    if (j == o + 1) {
                        add = 0;
                    } else {
                        add = add * stars(i, o + 1 - j) % M;
                    }
                }
                ans = (ans + add) % M;
            }
            cout << ans;
        } else {
            cout << 0;
        }
    }
    return 0;
}
