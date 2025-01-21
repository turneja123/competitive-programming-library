//https://dmoj.ca/problem/yac9p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const long long M = 1e9 + 7;

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
    int n;
    cin >> n;
    /*cout << binomial(2 * n, n) << endl;
    for (int p = 1; p <= n; p++) {
        long long ans = binomial(2 * n - p, n - p);
        cout << ans << " ";
        for (int j = 0; j < n - p; j++) {
            for (int i = 0; i < p; i++) {
                ans += binomial(n - 1 + j - i, j);
            }
            cout << ans << " ";
        }
        cout << endl;
    }*/
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int x = a[0], p = 0;
    while (p < n && a[p] == b[p] && a[p] == x) {
        p++;
    }
    int j = 0;
    if (p < n && a[p] == x) {
        while (p + j < n && a[p + j] == x) {
            j++;
        }
    } else if (p < n && b[p] == x) {
        while (p + j < n && b[p + j] == x) {
            j++;
        }
    }
    j = n - p - j;
    long long ans = binomial(2 * n - p, n - p);
    for (int k = 0; k < j; k++) {
        ans = (ans + binomial(n + k, k + 1) - binomial(n + k - p, k + 1) + M) % M;
    }
    cout << ans;
    return 0;
}
