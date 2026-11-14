//https://tlx.toki.id/contests/troc-44/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;

    ll ans = 0;
    ll ct = 4;
    for (int i = 2; i <= n; i++) {
        ans = (ans + ct * (i - 1) % M * modPow(i, i)) % M;
        ct = ct * 2 % M;
    }
    cout << ans;

    return 0;
}
