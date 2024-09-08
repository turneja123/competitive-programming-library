//https://codeforces.com/contest/1327/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;

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
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i == n) {
            cout << 10 << " ";
            continue;
        } else if (i == n - 1) {
            cout << 180 << " ";
            continue;
        }
        long long ans = (long long)2 * 10 * 9 * modPow(10, n - i - 1) % M + 9 * 9 * 10 * modPow(10, n - i - 2) % M * (n - i - 1) % M;
        cout << ans % M << " ";
    }
    return 0;
}
