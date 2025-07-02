//https://ocpc2025s.eolymp.space/en/compete/m9rs3cu3vp6lv7kjgk9aaqsa1s/problem/9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
};

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


vector<PT> calc(int l, int r) {
    if (l == r) {
        return a[l];
    }
    int mid = (l + r) / 2;
    vector<PT> lf = calc(l, mid);
    vector<PT> rt = calc(mid + 1, r);
    vector<PT> cur = minkowski_sum(lf, rt);
    return cur;

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        a[i].resize(3);
        for (int j = 0; j < 3; j++) {
            int x, y;
            cin >> x >> y;
            a[i][j] = PT(x, y);
        }
        if (cross(a[i][1] - a[i][0], a[i][2] - a[i][0]) < 0) {
            swap(a[i][1], a[i][2]);
        }

    }
    vector<PT> ans = calc(0, n - 1);
    ll best = 0;
    for (int i = 0; i < ans.size(); i++) {
        best = max(best, ans[i].x * ans[i].x + ans[i].y * ans[i].y);
        //cout << ans[i].x << " " << ans[i].y << endl;
    }
    cout << best;

    return 0;
}
