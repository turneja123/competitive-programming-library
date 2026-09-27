//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = double;

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int x, y, s, m;
    cin >> x >> y >> s >> m;
    if (abs(m - s) == 180) {
        cout << 0;
        return 0;
    }

    if (x == y) {
        cout << -1;
        return 0;
    }
    if (x > y) { // brzi mesec
        int l = (s + 180) % 360, r = (s - 180 + 360) % 360;
        int dist = min((l - m + 360) % 360, (r - m + 360) % 360);

        ld speed = 1.0 / (ld)y - 1.0 / (ld)x;
        cout << (ld)dist / speed / 360.0;
    } else {
        int l = (m + 180) % 360, r = (m - 180 + 360) % 360;
        int dist = min((l - s + 360) % 360, (r - s + 360) % 360);

        ld speed = 1.0 / (ld)x - 1.0 / (ld)y;
        cout << (ld)dist / speed / 360.0;
    }
    return 0;
}
