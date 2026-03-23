//https://atcoder.jp/contests/arc216/tasks/arc216_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

int a[N];
int pref[N];
int freq[N];

ll dp[N][N];
int mex[N][N];

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == -1) {
            pref[i]++;
        } else {
            freq[a[i]]++;
        }
        if (i != 0) {
            pref[i] += pref[i - 1];
        }
    }
    int m = pref[n - 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 1, ptr = 0; j <= n; j++) {
            ptr += !freq[j - 1];
            dp[i][j] = ((j == 0 ? 0 : dp[i][j - 1]) + (ptr > i ? 0 : fact[m - ptr] * factinv[i - ptr])) % M;
        }
    }
    for (int i = 0; i < n; i++) {
        vector<int> f(n, 0);
        for (int j = i, ptr = 0; j < n; j++) {
            if (a[j] != -1) {
                f[a[j]]++;
            }
            while (ptr < n && (f[ptr] || !freq[ptr])) {
                ptr++;
            }
            mex[i][j] = ptr;
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int z = pref[r] - (l == 0 ? 0 : pref[l - 1]);
        cout << dp[z][mex[l][r]] * fact[z] % M << endl;
    }

    return 0;
}
