//https://codeforces.com/contest/2164/problem/B
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
        int n;
        cin >> n;
        vector<int> e, o;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            if (a % 2 == 0) {
                e.push_back(a);
            } else {
                o.push_back(a);
            }
        }
        if (e.size() > 1) {
            cout << e[0] << " " << e[1] << endl;
            continue;
        }

        int l = -1, r = -1;
        if (e.size() == 1) {
            for (int i = 0; i < o.size(); i++) {
                if (e[0] > o[i] && (e[0] % o[i]) % 2 == 0) {
                    l = o[i], r = e[0];
                }
            }
        }

        for (int i = 1; i < o.size(); i++) {
            if ((o[i] % o[i - 1]) % 2 == 0) {
                l = o[i - 1], r = o[i];
            }
        }
        if (l == -1 && n < 50) {
            for (int i = 0; i < o.size(); i++) {
                for (int j = i + 1; j < o.size(); j++) {
                    if ((o[j] % o[i]) % 2 == 0) {
                        l = o[i], r = o[j];
                    }
                }
            }
        }

        if (l == -1) {
            cout << -1 << endl;
        } else {
            cout << l << " " << r << endl;
        }

    }
    return 0;
}
