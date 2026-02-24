//https://qoj.ac/contest/3347/problem/17152
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

map<ll, int> dp;

int calc(ll n) {
    if (n <= 8) {
        return n;
    }
    auto it = dp.find(n);
    if (it != dp.end()) {
        return it->second;
    }
    ll ans = n;
    for (int i = 2; i <= 20; i++) {
        ans = min(ans, calc(n / i) + n % i + i + 2);
    }
    return dp[n] = ans;
}

int main() {
    IOS;
    ll n;
    cin >> n;
    cout << calc(n);


    return 0;
}
