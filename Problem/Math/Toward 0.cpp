//https://atcoder.jp/contests/abc350/tasks/abc350_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

map<long long, long double> mp;

long double calc(long long n, long long a, long double x, long double y) {
    if (n == 0) {
        return 0;
    }
    auto it = mp.find(n);
    if (it != mp.end()) {
        return it->second;
    }

    long double cost = calc(n / a, a, x, y) + x;
    long double roll = ((long double)calc(n / 2, a, x, y) / 6.0 + calc(n / 3, a, x, y) / 6.0 + calc(n / 4, a, x, y) / 6.0 + calc(n / 5, a, x, y) / 6.0 + calc(n / 6, a, x, y) / 6.0 + (long double)y) / ((long double)1.0 - (long double)1.0 / 6.0);
    return mp[n] = min(cost, roll);
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    long long n, a, x, y;
    cin >> n >> a >> x >> y;
    cout << calc(n, a, x, y);
    return 0;
}

