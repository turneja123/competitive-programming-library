//https://ocpc2026w.eolymp.space/en/compete/7ds15ifh194hve0pf1tgf05pqs/problem/3
#pragma GCC target("popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll unsigned long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

ll b[N];

int main() {
    IOS;
    int n;
    cin >> n;
    b[0] = 1;
    int pref = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pref += a;
        if (i == 0) {
            cout << 0 << " ";
        } else if (pref % 2 == 1) {
            cout << i + 1 << " ";
        } else {
            int ans = i + 1, d = pref / 2;
            int l = d / 64, r = d % 64;
            ll mask = (r ? ((1ull << r) - 1) : ~0ull);
            for (int j = 0; j <= (d - 1) / 64; j++) {
                ll x = b[j + l] & b[j];
                if (r) {
                    x = ((b[j + l] >> r) | (b[j + l + 1] << (64 - r))) & b[j];
                }
                if (j == (d - 1) / 64) {
                    x &= mask;
                }
                ans -= __builtin_popcountll(x);
            }
            cout << ans << " ";
        }
        b[pref / 64] |= (1ull << (pref % 64));
    }


    return 0;
}
