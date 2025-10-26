//https://cses.fi/problemset/task/2190/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct P {
    ll x, y;
};

int sgn(__int128 v) {
    return (v > 0) - (v < 0);
}

int orient(const P& a, const P& b, const P& c) {
    __int128 x1 = b.x - a.x, y1 = b.y - a.y;
    __int128 x2 = c.x - a.x, y2 = c.y - a.y;
    return sgn(x1 * y2 - y1 * x2);
}

bool onSeg(const P& a, const P& b, const P& c) {
    if (orient(a, b, c) != 0) return false;
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

bool intersect(const P& a, const P& b, const P& c, const P& d) {
    int o1 = orient(a, b, c), o2 = orient(a, b, d);
    int o3 = orient(c, d, a), o4 = orient(c, d, b);

    if (o1 == 0 && onSeg(a, b, c)) return true;
    if (o2 == 0 && onSeg(a, b, d)) return true;
    if (o3 == 0 && onSeg(c, d, a)) return true;
    if (o4 == 0 && onSeg(c, d, b)) return true;

    return (o1 * o2 < 0 && o3 * o4 < 0);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        P A{x1, y1}, B{x2, y2}, C{x3, y3}, D{x4, y4};
        cout << (intersect(A, B, C, D) ? "YES" : "NO") << endl;
    }
    return 0;
}
