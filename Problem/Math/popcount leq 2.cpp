//https://atcoder.jp/contests/arc200/tasks/arc200_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

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

ll s2(ll n) {
    return n * (n - 1) / 2 % M;
}

ll s3(ll n) {
    return n * (n - 1) % M * (n - 2) % M * modPow(6, M - 2) % M;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        ll ans = (modPow(m + 1, n) - m * modPow(2, n - 1) % M - s2(m) * (modPow(2, n - 1) - 1) % M + 2 * M) % M;
        ans += (s2(m) + s3(m)) % M * (modPow(4, n - 1) - modPow(3, n) + 3 * modPow(2, n - 1) % M - 1 + 2 * M) % M;
        ans = (ans % M) * modPow(2, m) % M;
        cout << ans << endl;
    }
    return 0;
}
