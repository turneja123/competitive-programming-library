//https://codeforces.com/contest/2135/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
//#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 1e9;


int main() {
    //IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll best1 = -(1e12), best4 = 1e12;
        for (int i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            best1 = max(best1, x + y);
            best4 = min(best4, y - x);
        }
        ll d, a, b;
        cout << "? R " << INF << endl;
        cin >> d;
        cout << "? R " << INF << endl;
        cin >> d;
        cout << "? U " << INF << endl;
        cin >> d;
        cout << "? U " << INF << endl;
        cin >> a;

        cout << "? D " << INF << endl;
        cin >> d;
        cout << "? D " << INF << endl;
        cin >> d;
        cout << "? D " << INF << endl;
        cin >> d;
        cout << "? D " << INF << endl;
        cin >> b;

        ll x = (a + best1 + b - best4) / 2 - INF * 4;
        ll y = (a + best1 + best4 - b) / 2;
        cout << "! " << x << " " << y << endl;
    }

    return 0;
}
