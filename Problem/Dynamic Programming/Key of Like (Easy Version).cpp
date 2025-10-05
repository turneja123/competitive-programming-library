//https://codeforces.com/contest/2089/problem/C1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int K = 5005;
const ll M = 1e9 + 7;

ll dp[N][K];
ll ans[N];
ll inv[K];

void add(vector<ll> &a, int l, int r, ll val) {
    a[l] = (a[l] + val) % M;
    a[r + 1] = (a[r + 1] - val + M) % M;
}

void cyc_add(vector<ll> &a, int l, int k, ll val) {
    int n = a.size() - 1;
    int f = k / n, m = k % n;
    if (f) {
        add(a, 0, n - 1, val * f % M);
    }
    if (m) {
        int r = l + m - 1;
        if (r < n) {
            add(a, l, r, val);
        } else {
            add(a, l, n - 1, val);
            add(a, 0, r - n, val);
        }
    }
}

int main() {
    IOS;
    for (int i = 1; i < K; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k, z;
        cin >> n >> k >> z;
        for (int i = 0; i < n; i++) {
            ans[i] = 0;
            for (int j = 0; j <= k; j++) {
                dp[i][j] = 0;
            }
        }
        dp[0][k] = 1;
        for (int j = k; j >= 0; j--) {
            vector<ll> diff(n + 1, 0);
            for (int i = 0; i < n; i++) {
                if (j != k) {
                    ans[(i - 1 + n) % n] = (ans[(i - 1 + n) % n] + dp[i][j]) % M;
                }
                if (j != 0) {
                    cyc_add(diff, (i + 1) % n, j, inv[j] * dp[i][j] % M);
                }
            }
            if (j != 0) {
                ll s = 0;
                for (int i = 0; i < n; i++) {
                    s = (s + diff[i]) % M;
                    dp[i][j - 1] = s;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
