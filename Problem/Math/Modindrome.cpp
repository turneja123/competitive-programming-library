//https://www.codechef.com/problems/MODINDROME
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

long long pairs[N];

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
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            long long q = m / i, r = m % i;
            pairs[i] = (q * q * i + 2 * q * r + r + m) - m;
            pairs[i] %= M;
            ans = (ans + modPow(pairs[i], n / 2) * (n % 2 ? m : 1) % M) % M;
            ans = (ans - modPow(m, n / 2) * (n % 2 ? m : 1) % M + M) % M;
        }
        ans = (ans - modPow(m, n / 2) * (n % 2 ? m : 1) % M + M) % M;
        cout << ans << endl;
    }

    return 0;
}
