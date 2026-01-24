//https://cses.fi/problemset/task/2195/
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

int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
    }
    vector<PT> hull = convex_hull(p, 1);
    cout << hull.size() << endl;
    for (auto p : hull) {
        cout << p.x << " " << p.y << endl;
    }
    return 0;
}
