//https://codeforces.com/contest/1416/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> v{a};
    int best = 0; long long ans = 0;
    for (int k = 29; k >= 0; k--) {
        long long inv = 0, inv_other = 0;
        vector<vector<int>> nx;
        for (auto a : v) {
            vector<int> l, r;
            int ct0 = 0, ct1 = 0;
            for (auto x : a) {
                int c = x & (1 << k);
                if (c == 0) {
                    inv += ct1;
                    ct0++;
                    l.push_back(x);
                } else {
                    inv_other += ct0;
                    ct1++;
                    r.push_back(x);
                }
            }
            if (!l.empty()) {
                nx.push_back(l);
            }
            if (!r.empty()) {
                nx.push_back(r);
            }
        }
        ans += min(inv, inv_other);
        if (inv_other < inv) {
            best += 1 << k;
        }
        v = nx;
    }
    cout << ans << " " << best;

    return 0;
}
