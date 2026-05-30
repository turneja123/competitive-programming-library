//https://codeforces.com/contest/959/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    ll n;
    cin >> n;
    vector<ll> ans(45, 0);
    for (int i = 0; i < 45; i++) {
        ans[i] = (n - 1) / (1ll << i);
    }
    ll s = 0;
    for (int i = 44; i >= 0; i--) {
        for (int j = i + 1; j < 45; j++) {
            ans[i] -= ans[j];
        }
        s += ans[i] * (1ll << i);
    }
    cout << s;
    return 0;
}
