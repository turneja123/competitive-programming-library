//https://ocpc2026w.eolymp.space/en/compete/mi9vnankul3g72sfvkn0heloj8/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

ll modPow(ll a, ll y) {
    ll res = 1;
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
        ll n;
        cin >> n;
        ll ans = ((6 * n - 1) % M * modPow(2, n) % M + (n % 2 == 0 ? 1 : -1) + M) % M * modPow(9, M - 2) % M;
        cout << ans << endl;
    }

    return 0;
}
