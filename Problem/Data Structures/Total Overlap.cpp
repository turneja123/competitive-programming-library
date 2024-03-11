//solution for https://www.codechef.com/problems/TOVERLP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        map<ll, pair<ll, ll>> mp;
        for (int i = 0; i < n; i++) {
            ll l, r;
            cin >> l >> r;
            mp[l].first++;
            mp[r].first--;
        }
        for (int i = 0; i < m; i++) {
            ll l, r;
            cin >> l >> r;
            mp[l].second++;
            mp[r].second--;
        }
        int prev = -1;
        ll cnta = 0, cntb = 0, ans = 0;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (prev != -1) {
                ans += (it->first - prev) * cnta * cntb;
            }
            cnta += it->second.first;
            cntb += it->second.second;
            prev = it->first;
        }
        cout << ans << endl;
    }

    return 0;
}
