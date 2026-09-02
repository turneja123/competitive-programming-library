//https://codeforces.com/contest/2234/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 1e9 + 7;

ll inv[N];
ll fact[N];
ll factinv[N];
ll a[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll calc(int l, int r) {
    if (l > r) {
        return 1;
    }
    if (l == r) {
        return a[l] == 1;
    }
    int idx = -1;
    for (int i = 0; i <= r - l; i++) {
        int j = l + i;
        if ((ll)(j - l + 1) * (r - j + 1) == a[j]) {
            idx = j;
            break;
        }
        j = r - i;
        if ((ll)(j - l + 1) * (r - j + 1) == a[j]) {
            idx = j;
            break;
        }
    }
    if (idx == -1) {
        return 0;
    }
    return calc(l, idx - 1) * calc(idx + 1, r) % M * binomial(r - l, idx - l) % M;
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
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << calc(0, n - 1) << endl;
    }
    return 0;
}
