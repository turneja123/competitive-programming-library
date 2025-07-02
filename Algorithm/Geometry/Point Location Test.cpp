//https://cses.fi/problemset/task/2189
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        ll cross = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
        if (cross < 0) {
            cout << "RIGHT" << endl;
        } else if (cross > 0) {
            cout << "LEFT" << endl;
        } else {
            cout << "TOUCH" << endl;
        }
    }
    return 0;
}
