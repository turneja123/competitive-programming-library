//https://toph.co/p/fun-with-functions
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

__int128 modPow(__int128 a, __int128 y, __int128 m) {
    __int128 res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % m;
        }
        y /= 2;
        a = (a * a) % m;
    }
    return res;
}

long long geom(long long aa, long long xx, long long mm) {
    __int128 a = aa, x = xx, m = mm;
    if (a == 1) {
        __int128 ans = x % m;
        return ans;
    }
    __int128 M = m * (a - 1);
    __int128 ans = ((modPow(a, x, M) - 1) / (a - 1) + M) % M;
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long a, b, n, m, M;
        cin >> a >> b >> n >> m >> M;
        long long ans = geom(a, n, M) * b % M * m % M + modPow(a, n, M) * (m * (m + 1) / 2 % M) % M;
        cout << ans % M << endl;
    }

    return 0;
}
