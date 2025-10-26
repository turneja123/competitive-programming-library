//https://www.codechef.com/START208A/problems/PONEG
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
        vector<int> a(n), pref(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        }
        ll ans = 0;
        tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> tr;
        for (int i = 0; i < n; i++) {
            if (i < n - 1 && a[0] == -1 && pref[n - 1] - pref[i] >= 0 && a[i] == -1) {
                ans++;
            }
            if (i < n - 1 && a[n - 1] == -1 && pref[i] >= 0 && a[i + 1] == -1) {
                ans++;
            }
            if (i < n - 1 && a[0] == -1 && a[n - 1] == -1) {
                ans += tr.order_of_key(make_pair(pref[i], n + 1));
            }

            tr.insert(make_pair(pref[i], i));
        }
        cout << ans << endl;


    }
    return 0;
}
