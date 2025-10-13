//https://atcoder.jp/contests/arc208/tasks/arc208_c
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
        int c, x;
        cin >> c >> x;
        int n = c ^ x;
        if (n > x) {
            cout << n << endl;
        } else {
            if ((c - x) >= 0 && (c - x) % 2 == 0) {
                n = ((c - x) / 2) + (1 << 30);
                int z = (n ^ c) % n;
                if (z == x) {
                    cout << n << endl;
                } else {
                    cout << -1 << endl;
                }
            } else {
                cout << -1 << endl;
            }
        }

    }


    return 0;
}
