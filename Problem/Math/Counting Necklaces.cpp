//https://cses.fi/problemset/task/2209/
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
    int n, m;
    cin >> n >> m;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + modPow(m, __gcd(i, n))) % M;
    }
    cout << ans * modPow(n, M - 2) % M;
    return 0;
}
