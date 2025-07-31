//https://basecamp.eolymp.com/en/problems/11863
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> row(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> col(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
                row[i][j] = row[i][j - 1] + a[i][j];
            }
        }
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                col[i][j] = col[i - 1][j] + a[i][j];
            }
        }
        int q;
        cin >> q;
        map<tuple<int, int, int, int>, ll> mp;
        while (q--) {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            auto it = mp.find({l1, r1, l2, r2});
            if (it != mp.end()) {
                cout << it->second << endl;
                continue;
            }
            int L1 = l1, R1 = r1, L2 = l2, R2 = r2;
            ll ans = 0;
            int x = 1;
            while (l1 < l2 && r1 < r2) {
                int add = 0;
                add = col[l2][r1] - col[l1 - 1][r1] +col[l2][r2] - col[l1 - 1][r2] + row[l1][r2] - row[l1][r1 - 1] + row[l2][r2] - row[l2][r1 - 1];
                add -= a[l1][r1] + a[l1][r2] + a[l2][r1] + a[l2][r2];
                ans += (ll)add * x;
                l1++, l2--;
                r1++, r2--;
                x++;
            }
            if (l1 == l2) {
                ans += (ll)x * (row[l1][r2] - row[l1][r1 - 1]);
            } else if (r1 == r2) {
                ans += (ll)x * (col[l2][r1]  - col[l1 - 1][r1]);
            }
            cout << ans << endl;
            mp[{L1, R1, L2, R2}] = ans;
        }

    }
    return 0;
}
