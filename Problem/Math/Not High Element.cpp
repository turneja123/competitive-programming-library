//https://atcoder.jp/contests/arc217/tasks/arc217_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];
ll pw[N];

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1, pw[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
        pw[i] = pw[i - 1] * 2 % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k, mx = -1;
        cin >> n >> k;
        vector<int> f(n, 0);
        ll ans = 0;
        for (int i = 0; i < k; i++) {
            int a;
            cin >> a;
            a--;
            f[a] = 1;
            mx = max(mx, a);
            if (a != mx) {
                ans = (ans + pw[a]) % M;
            }
        }
        for (int i = n - 1, j = 0; i > mx; i--) {
            if (f[i]) {
                continue;
            }
            ans = (ans + pw[i] * j % M * inv[j + 1]) % M;
            j++;
        }
        for (int i = 0; i < mx; i++) {
            if (f[i]) {
                continue;
            }
            ans = (ans + pw[i]) % M;
        }
        cout << ans * fact[n - k] % M << endl;
    }

    return 0;
}
