//https://qoj.ac/contest/2509/problem/14102
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n;
    cin >> n;
    n++;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    ll ans = 0; int ok = 1;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < b[i]) {
            if (i == 0) {
                ok = 0;
                break;
            }
            ll take = (b[i] - a[i] + 1) / 2;
            a[i - 1] -= take;
            ans += take;
        }
    }
    if (!ok) {
        ans = -1;
    }
    cout << ans;

    return 0;
}
