//https://atcoder.jp/contests/arc211/tasks/arc211_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int x, y, z;
    cin >> x >> y >> z;
    if (x == y) {
        cout << x << " ";
        for (int i = 0; i < x; i++) {
            cout << 0 << " ";
        }
        cout << endl;
        cout << z << " ";
        for (int i = 0; i < z; i++) {
            cout << 0 << " ";
        }
        cout << endl;
        cout << z << " ";
        for (int i = 0; i < z; i++) {
            cout << 0 << " ";
        }
    } else if (x == 1) {
        cout << y << " ";
        for (int i = 0; i < y; i++) {
            cout << (i + 1) % 2 << " ";
        }
        cout << endl;
        cout << z << " ";
        for (int i = 0; i < z; i++) {
            cout << 1 << " ";
        }
        cout << endl;
        cout << z + y << " ";
        for (int i = 0; i < z; i++) {
            cout << 1 << " ";
        }
        for (int i = 0; i < y; i++) {
            cout << (i + 1) % 2 << " ";
        }
        cout << endl;

    } else {
        cout << y << " ";
        for (int i = 0; i < x; i++) {
            cout << 0 << " ";
        }
        for (int i = 0; i < y - x; i++) {
            cout << (i + 1) % 2 << " ";
        }
        cout << endl;
        cout << z << " ";
        for (int i = 0; i < z - x; i++) {
            cout << 1 << " ";
        }
        for (int i = 0; i < x; i++) {
            cout << 0 << " ";
        }
        cout << endl;
        cout << z + y - x << " ";
        for (int i = 0; i < z - x; i++) {
            cout << 1 << " ";
        }
        for (int i = 0; i < x; i++) {
            cout << 0 << " ";
        }
        for (int i = 0; i < y - x; i++) {
            cout << (i + 1) % 2 << " ";
        }

    }
    return 0;
}
