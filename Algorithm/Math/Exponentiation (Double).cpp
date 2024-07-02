//https://cses.fi/problemset/task/1095/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long mul(long long x, long long y, long long m){
    long long k = (x * (double)y / m) + 0.5, r = x * y - k * m;
    return r < 0 ? r + m : r;
}

long long modPow(long long x, long long y, long long m) {
    long long res = 1;
    while (y > 0) {
        if (y & 1) {
            res = mul(res, x, m);
        }
        x = mul(x, x, m);
        y >>= 1;
    }
    return res;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << modPow(a, b, 1e9 + 7) << endl;
    }

    return 0;
}
