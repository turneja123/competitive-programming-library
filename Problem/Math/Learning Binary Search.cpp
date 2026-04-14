//https://codeforces.com/contest/2211/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const ll M = 676767677;

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    if (n < k || n < 0 || k < 0) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll stars(ll n, ll k) {
    return binomial(n + k - 1, n);
}

int n, m;
ll ans = 0;

void calc(int l, int r, int d, int fl, int fr) {

    int mid = (l + r) / 2;
    int L = mid - l + 1, R = r - mid + 1;

    ans = (ans + d * (stars(n, m) - stars(n - L, m) * fl - stars(n - R, m) * fr + stars(n - L - R, m) * fl * fr + 2 * M)) % M;
    if (l <= mid - 1) {
        calc(l, mid - 1, d + 1, fl, 1);
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, d + 1, 1, fr);
    }


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
        ans = 0;
        cin >> n >> m;
        calc(0, n - 1, 1, 0, 0);
        cout << ans << endl;

    }

    return 0;
}
