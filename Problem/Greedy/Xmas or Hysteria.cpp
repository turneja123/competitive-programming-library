//https://codeforces.com/contest/2178/problem/D
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
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[i] = {x, i};
        }
        sort(a.begin(), a.end());
        vector<pair<int, int>> ans;
        if (m > 0) {
            if (2 * m > n) {
                cout << -1 << endl;
                continue;
            }
            for (int i = m; i + m < n; i++) {
                ans.push_back({a[i].second, a[i - 1].second});
            }
            ans.push_back({a[n - m].second, a[n - m - 1].second});
            for (int i = n - m + 1; i < n; i++) {
                ans.push_back({a[i].second, a[i - (n - m + 1)].second});
            }
            cout << ans.size() << endl;
            for (auto [l, r] : ans) {
                cout << l + 1 << " " << r + 1 << endl;
            }
        } else {
            ll s = 0;
            for (int i = 0; i < n - 1; i++) {
                s += a[i].first;
            }
            if (s < a[n - 1].first) {
                cout << -1 << endl;
                continue;
            }
            for (int i = 0; i < n - 1; i++) {
                if (a[i].first < a[n - 1].first) {
                    ans.push_back({a[i].second, a[n - 1].second});
                    a[n - 1].first -= a[i].first;
                } else {
                    ans.push_back({a[i].second, a[i + 1].second});
                }
            }
            cout << ans.size() << endl;
            for (auto [l, r] : ans) {
                cout << l + 1 << " " << r + 1 << endl;
            }

        }


    }
    return 0;
}
