//https://www.spoj.com/problems/SUBPAL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

gp_hash_table<int, int> mp;

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        string s;
        cin >> s;
        mp[0] = -1;
        int ans = 0, mask = 0, n = s.size();
        for (int i = 0; i < n; i++) {
            mask ^= (1 << (int)(s[i] - 'a'));
            auto it = mp.find(mask);
            if (it != mp.end()) {
                ans = max(ans, i - it->second);
            } else {
                mp[mask] = i;
            }
            for (int j = 0; j < 26; j++) {
                auto it_sub = mp.find(mask ^ (1 << j));
                if (it_sub != mp.end()) {
                    ans = max(ans, i - it_sub->second);
                }
            }
        }
        cout << "Case " << tt << ": " << ans << endl;
        mp.clear();
    }
    return 0;
}
