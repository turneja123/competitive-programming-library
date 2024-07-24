//https://judge.yosupo.jp/problem/gcd_convolution
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 998244353;
const int N = 1e6 + 5;

long long a[N];
long long b[N];
long long sum[2][N];
long long ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sum[0][i] = (sum[0][i] + a[j]) % M;
            sum[1][i] = (sum[1][i] + b[j]) % M;
        }
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = sum[0][i] * sum[1][i] % M;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i * 2; j <= n; j += i) {
            ans[i] = (ans[i] - ans[j] + M) % M;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
