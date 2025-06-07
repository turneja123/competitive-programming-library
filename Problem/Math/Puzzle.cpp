//https://codeforces.com/contest/2111/problem/F
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
        int p, s;
        cin >> p >> s;
        int g = __gcd(p, s);
        p /= g, s /= g;
        if (s * 4 < p) {
            cout << -1 << endl;
            continue;
        }
        if (s * 2 == p) {
            cout << 4 << endl;
            cout << "0 0" << endl << "0 1" << endl << "1 0" << endl << "1 1" << endl;
            continue;
        }
        if (s * 2 >= p) {
            int l, a;
            vector<pair<int, int>> ans;
            for (int i = 1; i < 50000; i++) {
                int need = i * i * p - 4 * i * s;
                if (need >= 0 && need % (2 * s - p) == 0) {
                    l = need / (2 * s - p);
                    for (int j = 0; j < i; j++) {
                        for (int k = 0; k < i; k++) {
                            ans.push_back(make_pair(j, k));
                        }
                    }
                    a = i;
                    break;
                }
            }
            for (int i = 0; i < l; i++) {
                ans.push_back(make_pair(0, a + i));
            }
            cout << ans.size() << endl;
            for (auto [x, y] : ans) {
                cout << x << " " << y << endl;
            }
        } else {
            vector<pair<int, int>> ans{{0, 0}};
            int P = 4, S = 1;
            int e = 0;
            for (int i = 1; i < 50000; i++) {
                int g = __gcd(P, S);
                if (P / g == p && S / g == s) {
                    e = 1;
                    break;
                }
                P += 2;
                S++;
                ans.push_back(make_pair(0, i));
            }
            if (e == 1) {
                cout << ans.size() << endl;
                for (auto [x, y] : ans) {
                    cout << x << " " << y << endl;
                }
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}
