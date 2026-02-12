//https://codeforces.com/contest/2002/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<ll, int>> v;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ll a; int b;
            cin >> a >> b;
            ll tim = 0;
            while (v.size()) {
                auto [xa, xb] = v.back();
                if (xa <= tim) {
                    v.pop_back();
                    continue;
                }
                if (xb == b) {
                    a += xa - tim;
                    v.pop_back();
                    continue;
                }
                tim = max(tim, xa);
                if (tim >= a) {
                    break;
                }
            }
            ans = max(ans, a);
            v.push_back({a, b});
            cout << ans << " ";
        }
        cout << endl;

    }
    return 0;
}
