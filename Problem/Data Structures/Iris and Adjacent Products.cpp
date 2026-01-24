//https://codeforces.com/contest/2006/problem/D
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
        int n, q, k;
        cin >> n >> q >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> ans(q);
        vector<tuple<int, int, int, int>> queries;
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries.push_back({l, r, (r - l + 1) / 2, 0});
        }
        vector<int> pref_cur(n), pref(n);

        int s = sqrt(k);
        for (int j = 1; j <= s; j++) {
            if (j * j == k) {
                continue;
            }
            int rt = k / j, lf = k / (j + 1) + 1;
            for (int i = 0; i < n; i++) {
                pref[i] = (i == 0 ? 0 : pref[i - 1]) + (a[i] >= lf && a[i] <= rt);
                pref_cur[i] = (i == 0 ? 0 : pref_cur[i - 1]) + (a[i] == j);
            }
            for (int i = 0; i < q; i++) {
                auto [l, r, need, ct] = queries[i];
                if (need <= 0) {
                    continue;
                }
                int have = pref_cur[r] - (l == 0 ? 0 : pref_cur[l - 1]) + ct;
                int bigs = pref[r] - (l == 0 ? 0 : pref[l - 1]);

                if (have >= bigs) {
                    get<3>(queries[i]) = have - bigs;
                    get<2>(queries[i]) -= bigs;
                } else {
                    bigs -= have;
                    get<2>(queries[i]) -= have;
                    need -= have;

                    ans[i] += min(need, (bigs + 1) / 2);
                    get<3>(queries[i]) = bigs % 2;
                    get<2>(queries[i]) -= bigs / 2;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
