//https://qoj.ac/contest/1452/problem/7934
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
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
};

PT p0;

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

void reorder_polygon(vector<PT> &p) {
  int pos = 0;
  for (int i = 1; i < p.size(); i++) {
    if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x)) pos = i;
  }
  rotate(p.begin(), p.begin() + pos, p.end());
}

vector<PT> minkowski_sum(vector<PT> a, vector<PT> b) {
  reorder_polygon(a); reorder_polygon(b);
  int n = a.size(), m = b.size();
  int i = 0, j = 0;
  a.push_back(a[0]); a.push_back(a[1]);
  b.push_back(b[0]); b.push_back(b[1]);
  vector<PT> c;
  while (i < n || j < m) {
    c.push_back(a[i] + b[j]);
    ld p = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (p >= 0 && i < n) ++i;
    if (p <= 0 && j < m) ++j;
  }
  return c;
}

bool cw(PT p1, PT p2, PT p3, bool include_collinear) {
    int o = orientation(p1, p2, p3);
    return o < 0 || (include_collinear && o == 0);
}

bool compare(PT p1, PT p2) {
    int o = orientation(p0, p1, p2);
    if (o > 0) return false;
    if (o < 0) return true;
    return dist(p0, p1) < dist(p0, p2);
}

vector<PT> convex_hull(vector<PT> p, bool include_collinear) {
    int n = p.size();
    ld ymn = 1e18, xmn = 1e18;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].y < ymn) {
            ymn = p[i].y;
            xmn = p[i].x;
            pos = i;
        } else if (p[i].y == ymn && p[i].x < xmn) {
            xmn = p[i].x;
            pos = i;
        }
    }
    swap(p[0], p[pos]);
    p0 = p[0];
    sort(p.begin() + 1, p.end(), compare); //sort cw
    if (include_collinear) {
        int i = (int)p.size() - 1;
        while (i >= 0 && orientation(p0, p[i], p.back()) == 0) i--;
        reverse(p.begin() + i + 1, p.end());
    }

    vector<PT> s;
    for (int i = 0; i < n; i++) {
        while (s.size() > 1 && !cw(s[s.size() - 2], s.back(), p[i], include_collinear)) {
            s.pop_back();
        }
        s.push_back(p[i]);
    }
    reverse(s.begin(), s.end()); //ccw
    return s;
}


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n;
    cin >> n;
    vector<PT> a(n);
    for (int i = 0; i < n; i++) {
        ld x, y;
        cin >> x >> y;
        a[i] = PT(-x, -y);
    }
    int m;
    cin >> m;
    vector<PT> b(m);
    for (int i = 0; i < m; i++) {
        ld x, y;
        cin >> x >> y;
        b[i] = PT(x, y);
    }
    a = convex_hull(a, 1);
    b = convex_hull(b, 1);
    vector<PT> p = minkowski_sum(a, b);
    shuffle(p.begin(), p.end(), gen);
    vector<PT> R;
    C c = enclosing_circle(0, p, R);
    cout << c.r << " " << c.cent.x << " " << c.cent.y;


    return 0;
}
