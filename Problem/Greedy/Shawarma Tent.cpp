//https://codeforces.com/contest/1271/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, x, y;
    cin >> n >> x >> y;
    vector<pair<int, int>> v{{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
    vector<int> ct(4, 0);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a < x) {
            ct[0]++;
        }
        if (a > x) {
            ct[1]++;
        }
        if (b < y) {
            ct[2]++;
        }
        if (b > y) {
            ct[3]++;
        }
    }
    int mx = 0, best = -1;
    for (int i = 0; i < 4; i++) {
        if (ct[i] > mx) {
            mx = ct[i];
            best = i;
        }
    }
    cout << mx << endl << v[best].first << " " << v[best].second;
    return 0;
}
