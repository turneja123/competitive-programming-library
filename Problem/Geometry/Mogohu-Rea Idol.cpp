//https://codeforces.com/contest/87/problem/E
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
};

int sign(ll x) {return (x > 0) - (x < 0);}
ll cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

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

int is_point_in_convex(vector<PT> &p, const PT& x) {
    int n = p.size();
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
    vector<vector<PT>> polygons;
    for (int i = 0; i < 3; i++) {
        int n;
        cin >> n;
        vector<PT> p(n);
        for (int i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            p[i] = PT(x, y);
        }
        polygons.push_back(p);
    }
    vector<PT> sum = minkowski_sum(minkowski_sum(polygons[0], polygons[1]), polygons[2]);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ll x, y;
        cin >> x >> y;
        PT pt = PT(3 * x, 3 * y);
        int o = is_point_in_convex(sum, pt);
        if (o <= 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
