//https://judge.yosupo.jp/problem/minimum_enclosing_circle
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

const ld eps = 1e-12;

struct PT {
    ld x, y;
    PT() { x = 0, y = 0; }
    PT(ld x, ld y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
};

int sign(ld x) { return (x > eps) - (x < -eps); }
ld cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
ld dist(PT a, PT b) { return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

bool line_line_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    ld a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
    ld a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
    ld det = a1 * b2 - a2 * b1;
    if (det == 0) return 0;
    ans = PT((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
    return 1;
}

struct C {
    PT cent;
    ld r;
    C() {}
    C(PT cent, ld r) : cent(cent), r(r) {}

    C(PT a, PT b) {
        r = dist(a, b) / 2.0;
        PT ab = PT(b.x - a.x, b.y - a.y);
        cent = PT(a.x + ab.x / 2.0, a.y + ab.y / 2.0);
    }

    C(PT a, PT b, PT c) {
        PT ab = PT(b.x - a.x, b.y - a.y);
        PT sab = PT(-ab.y, ab.x);
        PT bc = PT(c.x - b.x, c.y - b.y);
        PT sbc = PT(-bc.y, bc.x);

        PT ab_mid = PT(a.x + ab.x / 2.0, a.y + ab.y / 2.0);
        PT bc_mid = PT(b.x + bc.x / 2.0, b.y + bc.y / 2.0);

        if (!line_line_intersection(ab_mid, PT(ab_mid.x + sab.x, ab_mid.y + sab.y), bc_mid, PT(bc_mid.x + sbc.x, bc_mid.y + sbc.y), cent)) {
            vector<PT> v{a, b, c};
            r = 0.0;
            for (int i = 0; i < 3; i++) {
                for (int j = i + 1; j < 3; j++) {
                    C cur = C(v[i], v[j]);
                    if (cur.r > r) {
                        cent = cur.cent;
                        r = cur.r;
                    }
                }
            }
        } else {
            r = dist(cent, a);
        }
    }

};

bool contains(C c, PT p) {
    return dist(c.cent, p) - eps < c.r;
}


C enclosing_circle(int i, vector<PT> &p, vector<PT> R) {

    if (i == p.size() || R.size() == 3) {
        if (R.size() == 3) {
            return C(R[0], R[1], R[2]);
        } else if (R.size() == 2) {
            return C(R[0], R[1]);
        } else if (R.size() == 1) {
            C c = C(R[0], 0);
            return c;
        } else {
            C c = C(PT(0, 0), 0);
            return c;
        }
    }
    C c = enclosing_circle(i + 1, p, R);
    if (contains(c, p[i])) {
        return c;
    }
    R.push_back(p[i]);
    return enclosing_circle(i + 1, p, R);

}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        p[i] = PT(x, y);
    }
    vector<PT> orig = p;
    shuffle(p.begin(), p.end(), gen);
    vector<PT> R;
    C c = enclosing_circle(0, p, R);

    for (PT P : orig) {
        if (dist(c.cent, P) + eps > c.r) {
            cout << 1;
        } else {
            cout << 0;
        }
    }


    return 0;
}
