//https://cses.fi/problemset/task/2192/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
};

int sign(ll x) {
    return (x > 0) - (x < 0);
}

ll cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

int above(PT a, PT b) {
    return b.y >= a.y;
}

int on_segment(PT a, PT b, PT c) {
    if (cross(b - a, c - a) != 0) {
        return 0;
    }
    if (min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y)) {
        return 1;
    }
    return 0;
}

int crosses_ray(PT a, PT b, PT c) {
    return (above(a, b) - above(a, c)) * sign(cross(b - a, c - a)) > 0;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = PT(x, y);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        PT c = PT(x, y);
        int seg = 0;
        for (int j = 0; j < n; j++) {
            seg |= on_segment(p[j], p[(j + 1) % n], c);
        }
        if (seg) {
            cout << "BOUNDARY" << endl;
            continue;
        }
        for (int j = 0; j < n; j++) {
            seg += crosses_ray(c, p[j], p[(j + 1) % n]);
        }
        if (seg % 2 == 0) {
            cout << "OUTSIDE" << endl;
        } else {
            cout << "INSIDE" << endl;
        }
    }


    return 0;
}
