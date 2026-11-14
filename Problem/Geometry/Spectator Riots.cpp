//https://codeforces.com/contest/575/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int M = 1e5;

struct PT {
    ll x, y;

    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}

    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }

    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (const PT &a) const { return x < a.x || (x == a.x && y < a.y); }
};

int orientation(PT p1, PT p2, PT p3) {
    long long cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);

    if (cross > 0) return 1; // ccw
    if (cross < 0) return -1; // cw
    return 0; // collinear
}

bool cw(PT p1, PT p2, PT p3, bool include_collinear) {
    int o = orientation(p1, p2, p3);
    return o < 0 || (include_collinear && o == 0);
}

vector<PT> convex_hull(vector<PT> p, bool include_collinear) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    vector<PT> u, d;

    for (int i = 0; i < p.size(); i++) {
        while (u.size() >= 2 && cw(u[u.size() - 2], u.back(), p[i], !include_collinear)) {
            u.pop_back();
        }
        u.push_back(p[i]);
    }
    for (int i = p.size() - 1; i >= 0; i--) {
        while (d.size() >= 2 && cw(d[d.size() - 2], d.back(), p[i], !include_collinear)) {
            d.pop_back();
        }
        d.push_back(p[i]);
    }
    vector<PT> hull;
    for (int i = 0; i < u.size(); i++) {
        hull.push_back(u[i]);
    }
    for (int i = 1; i + 1 < d.size(); i++) {
        hull.push_back(d[i]);
    }
    return hull; //ccw
}

ll dist2(PT a, PT b) {
    PT d = a - b;
    return d.x * d.x + d.y * d.y;
}

ll cross2(PT a, PT b, PT c) {
    PT u = b - a, v = c - a;
    return u.x * v.y - u.y * v.x;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p;
    auto add = [&](ll x, ll y) {
        if (0 <= x && x <= M && 0 <= y && y <= M) {
            p.push_back({x, y});
        }
    };
    for (int i = 0; i < n; i++) {
        ll x, y, v;
        cin >> x >> y >> v;
        add(x - v, y);
        add(x + v, y);
        add(x, y - v);
        add(x, y + v);

        for (ll xx : {0, M}) {
            ll d = v - abs(x - xx);
            if (d >= 0) {
                add(xx, max(0ll, y - d));
                add(xx, min((ll)M, y + d));
            }
        }
        for (ll yy : {0, M}) {
            ll d = v - abs(y - yy);
            if (d >= 0) {
                add(max(0ll, x - d), yy);
                add(min((ll)M, x + d), yy);
            }
        }
    }
    vector<PT> hull = convex_hull(p, 0);
    int m = hull.size(), ans = 0;
    ld best = -1;
    for (int i = 0; i < m; i++) {
        PT a = hull[i], b = hull[(i + 1) % m], c = hull[(i + 2) % m];
        ld s = cross2(a, b, c);
        ld cur = (ld)dist2(a, b) * dist2(b, c) * dist2(c, a) / (s * s);
        if (cur > best) {
            best = cur;
            ans = i;
        }
    }

    for (int i = 0; i < 3; i++) {
        PT a = hull[(ans + i) % m];
        cout << a.x << " " << a.y << endl;
    }
    return 0;
}
