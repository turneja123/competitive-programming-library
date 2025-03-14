//https://cses.fi/problemset/task/2210
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;

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
    long long n;
    cin >> n;
    long long ans = 0;
    vector<long long> f(5, 1);
    /*while (n > 0) {
        long long m = max(1LL, 4 * (n - 1));
        f[1] = f[1] * modPow(2, __gcd(m, n - 1)) % M;
        f[2] = f[2] * modPow(2, __gcd(m, 2 * (n - 1))) % M;
        f[3] = f[3] * modPow(2, __gcd(m, 3 * (n - 1))) % M;
        f[4] = f[4] * modPow(2, __gcd(m, 4 * (n - 1))) % M;
        n -= 2;
    }*/
    long long r = (n % 2 == 0) ? n / 2 : (n - 1) / 2;
    long long add = (n % 2 == 0) ? 0 : 1;
    long long s = r * (n - r);
    f[1] = modPow(2, s + 1 + add);
    f[2] = modPow(2, 2 * s + add);
    f[3] = modPow(2, 4 * s + add);
    f[4] = 0;
    for (int i = 1; i <= 4; i++) {
        ans = (ans + f[i]) % M;
    }
    cout << ans * modPow(4, M - 2) % M << endl;
    return 0;
}
