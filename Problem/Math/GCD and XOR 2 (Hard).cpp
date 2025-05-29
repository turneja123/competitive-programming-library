//https://www.codechef.com/START188A/problems/GCDXOR2HD
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5000;
const __int128 M = 998244353;

long long s[N];

__int128 modPow(__int128 a, __int128 y, __int128 MOD) {
    __int128 res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % MOD;
        }
        y /= 2;
        a = (a * a) % MOD;
    }
    return res;
}


int main() {
	IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, d;
        cin >> n >> d;
        int m = 1 << (32 - __builtin_clz(d));
        for (int i = 0; i < m; i++) {
            int c = d & (d * i);
            s[i] = (i == 0 ? 0 : s[i - 1]) + (c == 0);
        }
        __int128 MOD = M * d * m;
        long long j = (modPow(2, n, MOD) - 1 - d + MOD) % MOD;
        __int128 ans = (j / d / m * s[m - 1] % M + s[(j / d) % m] - 1 + M) % M;
        cout << (long long)ans << endl;
    }
	return 0;
}
