//https://codeforces.com/contest/2152/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int pref[N];
int add[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            x -= 2;
            if (x == 0) {
                pref[i] = 1;
                add[i] = 0;
            } else {
                pref[i] = 32 - __builtin_clz(x);
                if (__builtin_popcount(x + 1) == 1) {
                    add[i] = 1;
                } else {
                    add[i] = 0;
                }
            }
            if (i != 0) {
                add[i] += add[i - 1];
                pref[i] += pref[i - 1];
            }
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            int ans = pref[r] - (l == 0 ? 0 : pref[l - 1]) + (add[r] - (l == 0 ? 0 : add[l - 1])) / 2;
            cout << ans << endl;
        }

    }
    return 0;
}
