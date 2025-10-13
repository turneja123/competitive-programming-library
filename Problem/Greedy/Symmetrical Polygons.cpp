//https://codeforces.com/contest/2153/problem/C
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
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            mp[a]++;
        }
        vector<pair<int, int>> v;
        vector<int> o;
        for (auto [x, f] : mp) {
            v.push_back({x, f});
        }
        ll best = 0, cur = 0; int ct = 0;
        for (auto [x, f] : v) {
            if (f % 2 == 0) {
                cur += (ll)f * x;
                ct += f;
                if (ct > 2) {
                    best = max(best, cur);
                }
            } else {
                cur += (ll)(f - 1) * x;
                ct += f - 1;
                if (ct > 2) {
                    best = max(best, cur);
                }
                o.push_back(x);
            }
        }
        if (o.size()) {
            sort(o.begin(), o.end(), greater<int>());
            for (int i = 0; i < o.size() - 1; i++) {
                auto x1 = o[i];
                auto x2 = o[i + 1];
                cur += x1 + x2;
                ct += 2;
                if (ct > 2 && cur - max(x1, x2) > max(x1, x2)) {
                    best = max(best, cur);
                }
                cur -= x1 + x2;
                ct -= 2;
            }
            for (int i = 0; i < o.size(); i++) {
                auto x = o[i];
                cur += x;
                ct += 1;
                if (ct > 2 && cur - x > x) {
                    best = max(best, cur);
                }
                cur -= x;
                ct -= 1;
            }

        }
        cout << best << endl;


    }
    return 0;
}
