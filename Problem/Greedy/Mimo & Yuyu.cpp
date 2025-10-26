//https://codeforces.com/contest/2155/problem/E
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
        int n, m, k;
        cin >> n >> m >> k;
        map<int, int> mp;
        ll s = 0;
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            s +=
            mp[y]++;
        }
        string ans = "Yuyu";
        if (n == 1) {
            if (mp[2] % 2 == 1) {
                ans = "Mimo";
            }
        } else {
            for (auto [z, d] : mp) {
                if (d % 2 == 1 && z != 1) {
                    ans = "Mimo";
                }
            }
        }
        cout << ans << endl;
    }


    return 0;
}
