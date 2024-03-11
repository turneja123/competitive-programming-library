//solution for https://cses.fi/problemset/task/1095/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

ll modPow(ll x, ll y) {
    if (x == 0 && y == 0) {
        return 1;
    }
    ll res = 1;
    x = x % M;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % M;
        }
        y >>= 1;
        x = (x * x) % M;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        cout << modPow(a, b) << endl;
    }
    return 0;
}
