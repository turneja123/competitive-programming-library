//https://ocpc2026w.eolymp.space/en/compete/ig3v7lohgt0vd43nv48bk2lb4o/problem/10
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const ll M = 998244353;

int mask[N];
ll e[2], o[2];

int main() {
    IOS;
    int n, m, c;
    cin >> n >> m >> c;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < c; k++) {
            mask[j] |= 1 << k;
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            int b = s[j] - 'a';
            mask[j] &= ~(1 << b);
        }
    }
    int E = 0, O = 0;
    e[0] = 1, e[1] = 1, o[0] = 1, o[1] = 1; int z = 1;
    for (int i = 0; i < m; i++) {
        int pc = (mask[i] == 0 ? 0 : __builtin_popcount(mask[i]));
        if (pc % 2 == 0) {
            E = 1;
            e[0] = e[0] * pc % M;
            e[1] = e[1] * (c - pc) % M;
        } else {
            O = 1;
            o[0] = o[0] * pc % M;
            o[1] = o[1] * (c - pc) % M;
        }
        if (pc == 0) {
            z = 0;
        }
    }

    ll ans = (E && O ? (e[1] * o[0] + e[0] * o[1] * z) % M : 0);
    cout << ans;



    return 0;
}
