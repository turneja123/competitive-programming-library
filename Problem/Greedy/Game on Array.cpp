//https://codeforces.com/contest/2147/problem/D
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
        map<int, int> mp;
        ll s = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            s += a;
            mp[a]++;
        }
        vector<int> odds;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            if (it->first % 2 == 1) {
                odds.push_back(it->second);
            }
        }
        sort(odds.begin(), odds.end(), greater<int>());
        ll diff = 0;
        for (int i = 0; i < odds.size(); i++) {
            if (i % 2 == 0) {
                diff += odds[i];
            } else {
                diff -= odds[i];
            }
        }
        ll b = (s - diff) / 2, a = s - b;
        cout << a << " " << b << endl;
    }
    return 0;
}
