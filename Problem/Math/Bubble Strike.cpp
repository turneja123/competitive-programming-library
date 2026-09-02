//https://codeforces.com/contest/1599/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

int main() {
    IOS;

    int n; ld p;
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        ld tot = (ld)n * (ld)(n - 1) * (ld)(n - 2) / (ld)6;
        int j = n - i;
        ld p1 = (j < 2 ? 0 : (ld)j * (ld)(j - 1) / (ld)2 * (ld)i / tot);
        ld p2 = (i < 2 ? 0 : (ld)j * (ld)i * (ld)(i - 1) / (ld)2 / tot);
        ld p3 = (i < 3 ? 0 : (ld)i * (ld)(i - 1) * (ld)(i - 2) / (ld)6 / tot);
        ld s = p1 * 0.5 + p2 + p3;
        if (s >= p) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}
