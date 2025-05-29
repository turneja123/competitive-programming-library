//https://codeforces.com/contest/2066/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, global = 0;
        cin >> n;
        map<int, long long> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        mp[0] = 3;
        global = a[0];
        int last = 0;
        for (int i = 1; i < n; i++) {
            if (last) {
                mp[global] = mp[global] * 3 % M;
            }
            auto it = mp.find(a[i] ^ global);
            if (it != mp.end()) {
                mp[global] = (mp[global] + it->second * 2) % M;
                last = 1;
            } else {
                last = 0;
            }
            global ^= a[i];
        }
        long long ans = 0;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans = (ans + it->second) % M;
        }
        cout << ans << endl;
    }
    return 0;
}
