//https://www.spoj.com/problems/SPOINTS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long INF = 1e18;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
};

PT p0;

ll distsq(PT p1, PT p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

ll cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

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

bool compare(PT p1, PT p2) {
    int o = orientation(p0, p1, p2);
    if (o > 0) return false;
    if (o < 0) return true;
    return distsq(p0, p1) < distsq(p0, p2);
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
    ll p = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (p >= 0 && i < n) ++i;
    if (p <= 0 && j < m) ++j;
  }
  return c;
}

vector<PT> convex_hull(vector<PT> p, bool include_collinear) {
    int n = p.size();
    ll ymn = INF, xmn = INF;
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

int on_segment(PT a, PT b, PT c) {
    if (cross(b - a, c - a) != 0) {
        return 0;
    }
    if (min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y)) {
        return 1;
    }
    return 0;
}

int is_point_in_convex(vector<PT> &p, const PT& x) {
    int n = p.size();
    if (n == 1) {
        return !(p[0] == x);
    }
    if (n == 2) {
        return !(on_segment(p[0], p[1], x));
    }
    assert(n >= 3);
    int a = orientation(p[0], p[1], x),
    b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}

int main() {
    IOS;
    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0) {
            break;
        }
        vector<PT> pa(n), pb(m);
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            pa[i] = PT(x, y);
        }
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            pb[i] = PT(-x, -y);
        }
        vector<PT> hulla = convex_hull(pa, false);
        vector<PT> hullb = convex_hull(pb, false);
        vector<PT> hull = minkowski_sum(hulla, hullb);
        string ans = "YES";
        if (is_point_in_convex(hull, PT(0, 0)) != 1) {
            ans = "NO";
        }
        cout << ans << endl;
    }
    return 0;
}
