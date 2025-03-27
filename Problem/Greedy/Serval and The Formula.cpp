//https://codeforces.com/contest/2085/problem/C
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
        int x, y;
        cin >> x >> y;
        if (x == y) {
            cout << -1 << endl;
            continue;
        }
        if (x < y) {
            swap(x, y);
        }
        int k = 32 - __builtin_clz(x);
        int need = 1 << k;
        cout << need - x << endl;
    }
    return 0;
}
