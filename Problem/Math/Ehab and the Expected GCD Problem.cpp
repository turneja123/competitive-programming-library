//https://codeforces.com/contest/1174/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int d[N];
int spf[N];
int is_prime[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            d[i]++;
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
                int t = j;
                while (t % i == 0) {
                    d[j]++;
                    t /= i;
                }
            }
        }
    }
}

vector<int> factor(int n) {
    vector<int> f;
    while (n > 1) {
        int p = spf[n];
        while (n % p == 0) {
            n /= p;
            f.push_back(p);
        }
    }
    return f;
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    sieve(N);
    int n;
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(d[i], mx);
    }
    vector<int> go;
    for (int i = 1; i <= n; i++) {
        if (d[i] == mx) {
            go.push_back(i);
        }
    }
    ll ans = 0;
    for (int x : go) {
        vector<int> f = factor(x);
        do {
            ll cur = 1;
            int m = n - 1, prod = x;
            for (int i = 0; i < f.size(); i++) {
                prod /= f[i];

                int items = n / prod - n / (prod * f[i]);
                cur = cur * fact[items] % M * binomial(m - 1, items - 1) % M;
                m -= items;
            }
            ans = (ans + cur) % M;
        } while (next_permutation(f.begin(), f.end()));
    }
    cout << ans;


    return 0;
}
