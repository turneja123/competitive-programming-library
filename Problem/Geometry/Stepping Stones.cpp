//https://ocpc2025s.eolymp.space/en/compete/s47ok89k9t7evbt1ovdfvc933c/problem/9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 8e18 + 1;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
};

#define up(u,v)         (dot(u,v) > 0)
#define down(u,v)       (dot(u,v) < 0)
#define dr(u,Vi,Vj)     (dot(u, (Vi)-(Vj)))
#define above(u,Vi,Vj)  (dr(u,Vi,Vj) > 0)
#define below(u,Vi,Vj)  (dr(u,Vi,Vj) < 0)

ll dot(PT a, PT b) {
    return a.x * b.x + a.y * b.y;
}

PT extreme(vector<PT> &p, PT v) {
    PT dir = PT(-v.y, v.x);
    int n = p.size();
    if (n < 10) {
        ll best = -INF; PT ret;
        for (int i = 0; i < n; i++) {
            if (dot(dir, p[i]) > best) {
                best = dot(dir, p[i]);
                ret = p[i];
            }
        }
        return ret;
    }
    int a, b, c;
    PT A, C;
    int upA, upC;
    a = 0, b = n;
    A = p[1] - p[0];
    upA = up(dir, A);
    if (!upA && !above(dir, p[n - 1], p[0])) {
        return p[0];
    }
    for (;;) {
        c = (a + b) / 2;
        C = p[(c + 1) % n] - p[c];
        upC = up(dir, C);
        if (!upC && !above(dir, p[c - 1], p[c])) {
            return p[c];
        }
        if (upA) {
            if (!upC) {
                b = c;
            } else {
                if (above(dir, p[a], p[c])) {
                    b = c;
                } else {
                    a = c;
                    A = C;
                    upA = upC;
                }
            }
        } else {
            if (upC) {
                a = c;
                A = C;
                upA = upC;
            } else {
                if (below(dir, p[a], p[c])) {
                    b = c;
                } else {
                    a = c;
                    A = C;
                    upA = upC;
                }
            }
        }

    }
    return p[0];
}

int side(ll dx, ll dy, PT &p, PT &d) {
    ll cross = dx * (p.y - d.y) - dy * (p.x - d.x);
    if (cross < 0) {
        return -1;
    }
    if (cross == 0) {
        return 0;
    }
    return 1;
}

ll cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }

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

vector<PT> a[N];
vector<PT> segtree[4 * N];

PT addp, addn;

void query(int l, int r, int lq, int rq, ll dx, ll dy, int node) {
    if (l > rq || r < lq) {
        return;
    }
    if (l >= lq && r <= rq) {
        PT lf = extreme(segtree[node], {dx, dy});
        PT rt = extreme(segtree[node], {-dx, -dy});
        addp = addp + lf - rt;
        addn = addn - lf + rt;
        return;
    }
    int mid = (l + r) / 2;
    query(l, mid, lq, rq, dx, dy, 2 * node + 1);
    query(mid + 1, r, lq, rq, dx, dy, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = minkowski_sum(segtree[2 * node + 1], segtree[2 * node + 2]);
}



int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; j++) {
            ll x, y;
            cin >> x >> y;
            a[i][j] = PT(x, y);
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < m; i++) {
        ll x1, y1, x2, y2, dx, dy; int l, r;
        cin >> x1 >> y1 >> x2 >> y2 >> dx >> dy >> l >> r;
        l--, r--;
        addp = PT(0, 0);
        addn = PT(0, 0);
        query(0, n - 1, l, r, dx, dy, 0);
        PT st = {x1, y1};
        PT need = {x2, y2};
        PT enp = st + addp, enn = st + addn;
        if (side(dx, dy, st, need) != side(dx, dy, enp, need) || side(dx, dy, st, need) != side(dx, dy, enn, need)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
