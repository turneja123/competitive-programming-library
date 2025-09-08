//https://codeforces.com/contest/2138/problem/A
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
        ll n, x;
        cin >> n >> x;
        vector<int> ans;
        ll y = (1ll << (n + 1)) - x;
        while (x != y) {
            if (x < y) {
                pair<ll, ll> p = {2 * x, y - x};
                tie(x, y) = p;
                ans.push_back(1);
            } else {
                pair<ll, ll> p = {x - y, 2 * y};
                tie(x, y) = p;
                ans.push_back(2);
            }
        }
        cout << ans.size() << endl;
        if (ans.size()) reverse(ans.begin(), ans.end());
        for (int i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
