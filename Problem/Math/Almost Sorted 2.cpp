//https://atcoder.jp/contests/abc431/tasks/abc431_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int N = 1e6 + 5;

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
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int last = a[0], ct = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != last) {
            b.push_back({last, ct});
            last = a[i];
            ct = 1;
        } else {
            ct++;
        }
    }
    b.push_back({last, ct});
    ll ans = 1;
    int r = b.size() - 1, k = 1;
    for (int i = b.size() - 1; i >= 0; i--) {
        auto [x, m] = b[i];
        while (x < b[r].first - d) {
            k -= b[r].second;
            r--;
        }
        ans = ans * binomial(m + k - 1, k - 1) % M;
        k += m;
    }
    cout << ans;

    return 0;
}
