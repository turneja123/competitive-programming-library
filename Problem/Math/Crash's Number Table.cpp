//https://www.spoj.com/problems/TABLE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e7 + 5;
const long long M = 20101009;

int a[N];
long long sum[N];
long long inv[N];

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

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    if (n > m) {
        swap(n, m);
    }
    sum[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= m; i++) {
        sum[i] = (sum[i - 1] + i) % M;
        inv[i] = M - (M / i) * inv[M % i] % M;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = sum[n / i] * i % M * sum[m / i] * i % M;
    }
    long long ans = 0;
    for (int i = n; i >= 1; i--) {
        long long diff = 0;
        for (int j = 2 * i; j <= n; j += i) {
            diff += a[j];
        }
        diff %= M;
        a[i] = (a[i] - diff + M) % M;
        ans += (long long)a[i] * inv[i] % M;
    }
    cout << ans % M << endl;

    return 0;
}
