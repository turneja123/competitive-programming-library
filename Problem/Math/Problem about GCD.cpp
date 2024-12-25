//https://codeforces.com/contest/2043/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long l, r, g;
        cin >> l >> r >> g;
        long long lf = l / g, rt = r / g;
        if (l % g != 0) {
            lf++;
        }
        long long best = -1;
        pair<long long, long long> ans = make_pair(-1, -1);
        for (long long i = lf; i <= min(lf + 100, rt); i++) {
            for (long long j = rt; j >= max(i, rt - 100); j--) {
                long long x = g * i, y = g * j;
                if (y - x <= best) {
                    break;
                }
                if (__gcd(i, j) == 1) {
                    best = y - x;
                    ans = make_pair(x, y);
                }
            }
        }
        cout << ans.first << " " << ans.second << endl;
    }
    return 0;
}
