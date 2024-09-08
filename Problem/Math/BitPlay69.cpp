//https://www.spoj.com/problems/BT69/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long INF = 1e18;

long long calc(long long d, long long n, long long m, long long ans) {
    if (d == -1) {
        return INF;
    }
    if (n == ((1ll << (d + 1)) - 1) && m == ((1ll << (d + 1)) - 1)) {
        return INF;
    }
    long long x = n & (1ll << d), y = m & (1ll << d);
    if (x == 0 && y == 0) {
        return min(ans + (1ll << d), calc(d - 1, n - x, m - y, ans));
    } else if (x == 0 && y != 0) {
        return calc(d - 1, n - x, m - y, ans + (1ll << d));
    } else if (x != 0 && y == 0) {
        return ans;
    } else {
        return calc(d - 1, n - x, m - y, ans);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n, m;
        cin >> n >> m;
        if (n > m) {
            cout << 0 << endl;
        } else {
            cout << calc(61, n, m, 0) << endl;
        }
    }


    return 0;
}
