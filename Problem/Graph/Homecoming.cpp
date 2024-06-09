//https://www.spoj.com/problems/HOMEC/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

map<vector<int>, int> mp;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        if (m > n) {
            cout << -1 << endl;
            continue;
        }
        vector<int> start(3, 0);
        start[0] = n, start[1] = m, start[2] = 0;
        mp[start] = 0;
        queue<vector<int>> q;
        q.push(start);
        int ans = -1;
        while (q.size()) {
            vector<int> v = q.front();
            q.pop();
            int ln = v[0], lm = v[1], rn = n - ln, rm = m - lm, sgn = v[2], d = mp[v];
            if (ln == 0 && lm == 0) {
                ans = mp[v];
                break;
            }
            if (sgn == 0) {
                for (int dn = 0; dn <= k; dn++) {
                    for (int dm = 0; dn + dm <= k; dm++) {
                        if (dn + dm == 0) {
                            continue;
                        }
                        if (dn != 0 && dm > dn) {
                            break;
                        }
                        int xln = ln - dn, xlm = lm - dm, xrn = rn + dn, xrm = rm + dm;
                        v[0] = xln, v[1] = xlm, v[2] = 1;
                        if (xln < 0 || xlm < 0) {
                            continue;
                        }
                        if (xln != 0 && xlm > xln) {
                            continue;
                        }
                        if (xrn != 0 && xrm > xrn) {
                            continue;
                        }
                        auto it = mp.find(v);
                        if (it == mp.end()) {
                            mp[v] = d + 1;
                            q.push(v);
                        }
                    }
                }
            } else {
                for (int dn = 0; dn <= k; dn++) {
                    for (int dm = 0; dn + dm <= k; dm++) {
                        if (dn + dm == 0) {
                            continue;
                        }
                        if (dn != 0 && dm > dn) {
                            break;
                        }
                        int xln = ln + dn, xlm = lm + dm, xrn = rn - dn, xrm = rm - dm;
                        v[0] = xln, v[1] = xlm, v[2] = 0;
                        if (xrn < 0 || xrm < 0) {
                            continue;
                        }
                        if (xln != 0 && xlm > xln) {
                            continue;
                        }
                        if (xrn != 0 && xrm > xrn) {
                            continue;
                        }
                        auto it = mp.find(v);
                        if (it == mp.end()) {
                            mp[v] = d + 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        cout << ans << endl;
        mp.clear();
    }
    return 0;
}
