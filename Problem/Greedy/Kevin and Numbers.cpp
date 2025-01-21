//https://codeforces.com/contest/2061/problem/D
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
        int n, m;
        cin >> n >> m;
        multiset<int> sta, stb;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            sta.insert(a);
        }
        for (int i = 0; i < m; i++) {
            int b;
            cin >> b;
            stb.insert(b);
        }
        while (sta.size() && stb.size()) {
            int x = *sta.begin(), y = *stb.begin();
            if (x > y) {
                break;
            }
            auto it = sta.find(y);
            if (it != sta.end()) {
                sta.erase(it);
                stb.erase(stb.begin());
            } else {
                stb.erase(stb.begin());
                stb.insert(y / 2);
                stb.insert(y / 2 + y % 2);
            }
        }
        if (stb.empty() && sta.empty()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
