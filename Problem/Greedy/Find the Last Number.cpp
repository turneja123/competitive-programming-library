//https://codeforces.com/contest/2156/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int b = 31 - __builtin_clz(n);

        vector<int> l, r, go;
        for (int i = 0; i < n - 1; i++) {
            go.push_back(i);
        }
        int ans = 0, full = 0;
        for (int k = 0; k <= b; k++) {
            int cta = 0;
            for (int i = 1; i <= n; i++) {
                int c = i & full;
                if (c == ans) {
                    int ca = i & (1 << k);
                    cta += ca > 0;
                }
            }

            int c = 1 << k, cur = 0;
            for (int i : go) {
                cout << "? " << i + 1 << " " << c << endl;
                int z;
                cin >> z;
                if (z == 1) {
                    cur++;
                    r.push_back(i);
                } else {
                    l.push_back(i);
                }
            }
            if (cur == cta) {
                go = l;
            } else {
                ans += 1 << k;
                go = r;
            }
            full += 1 << k;
            l.clear();
            r.clear();
        }
        cout << "! " << ans << endl;

    }

    return 0;
}
