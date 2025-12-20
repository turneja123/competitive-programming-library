//https://qoj.ac/contest/2668/problem/15446
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 1e9 + 7;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

ll dp[N];
ll fact[N];

int main() {
    IOS;
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    vector<int> f = {0, 1};
    for (int i = 2; i < 30; i++) {
        f.push_back(f[i - 1] + f[i - 2]);
    }
    int n;
    cin >> n;
    if (n < 3) {
        cout << 0;
        return 0;
    }
    ll ans = 0;
    for (int i = 3; i <= n; i++) {
        ans = (ans + modPow(n, i)) % M;
    }
    for (int j = 0; j <= n; j++) {
        dp[j] = 1;
    }
    for (int i = 2; max(i, f[i]) <= n; i++) {
        for (int j = f[i]; j <= n; j++) {
            dp[j] = (dp[j] + dp[j - f[i]]) % M;
        }
        for (int j = n; j >= f[i - 1]; j--) {
            dp[j] = (dp[j] - dp[j - f[i - 1]]) % M;
        }
        ll s = 0;
        for (int j = 0; j <= n - f[i]; j++) {
            s = (s + dp[j]) % M;
        }
        if (i != 2) {
            ans = (ans - s * fact[i] % M * modPow(2, M - 2) % M + M) % M;
        }
        for (int j = f[i - 1]; j <= n; j++) {
            dp[j] = (dp[j] + dp[j - f[i - 1]]) % M;
        }
        s = 0;
        for (int j = 0; j <= n - f[i] - f[i - 1]; j++) {
            s = (s + dp[j]) % M;
        }
        if (i != 2) {
            ans = (ans - s * fact[i] + M) % M;
        }
    }
    cout << ans;


    return 0;
}
