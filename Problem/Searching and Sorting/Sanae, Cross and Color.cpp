//https://codeforces.com/contest/2228/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

vector<int> pos[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> seen(n, 0), pref(n, 0);
        int l = n + 1, r = -1;
        vector<int> ct(n, 0);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            l = min(l, x);
            r = max(r, x);
            seen[y] = 1;
            pos[x].push_back(y);
            ct[y]++;
        }

        for (int i = 0; i < n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + seen[i];
        }

        int ptrl = 0, ptrr = n - 1;

        int mnl = n + 1, mxr = -1;
        ll ans = 0;

        for (int i = l; i < r; i++) {
            if (pos[i].empty()) {
                continue;
            }
            for (int y : pos[i]) {
                mnl = min(mnl, y);
                mxr = max(mxr, y);
                ct[y]--;
            }
            while (ct[ptrl] == 0) {
                ptrl++;
            }
            while (ct[ptrr] == 0) {
                ptrr--;
            }
            int L = max(mnl, ptrl);
            int R = min(mxr, ptrr);
            if (R > L) {
                ans += pref[R - 1] - pref[L] + 1;
            }
        }
        cout << ans << endl;

        for (int i = 0; i < n; i++) {
            pos[i].clear();
        }
    }
    return 0;
}
