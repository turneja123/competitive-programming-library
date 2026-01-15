//https://atcoder.jp/contests/arc212/tasks/arc212_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; i + j < n - 3; j++) {
            int k = n - 3 - i - j;
            ll p = (ll)i * j % M * k % M;
            ans = (ans + p * ((n - 1) - max({i, j, k}))) % M;
        }
    }
    cout << ans;
    return 0;
}
