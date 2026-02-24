//https://atcoder.jp/contests/arc215/tasks/arc215_c
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
        vector<tuple<int, int, int>> a;
        multiset<int> l_y, l_z, r_y, r_z;
        for (int i = 0; i < n; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            a.push_back({x, y, z});
            r_y.insert(y), r_z.insert(z);
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int ans = n;
        for (int i = 0; i < n; i++) {
            auto [x, y, z] = a[i];
            r_y.erase(r_y.find(y));
            r_z.erase(r_z.find(z));
            l_y.insert(y);
            l_z.insert(z);
            if (i == n - 1 || x == get<0>(a[i + 1])) {
                continue;
            }
            if (*l_y.begin() > *r_y.rbegin() && *l_z.begin() > *r_z.rbegin()) {
                ans = i + 1;
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}

