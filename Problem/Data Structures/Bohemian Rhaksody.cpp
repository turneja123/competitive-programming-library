//https://dmoj.ca/problem/bohemianrhaksody
#pragma GCC target("avx2")
//#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int H, W;

struct PT {
    int x;
    int y;
    PT() {}
    PT(int _x, int _y) {
        x = _x;
        y = _y;
    }
    bool operator < (PT a) const { return (a.x != x ? x < a.x : y < a.y); }
};

struct Ival {
    int w;
    int x;
    int y;
    Ival() {}
    Ival(int _w, int _x, int _y) {
        w = _w;
        x = _x;
        y = _y;
    }
};

vector<PT> a;
vector<int> b;
long long ans = 0;

vector<Ival> sl, sr;

PT ps[N], tmp[N];

ll cost(int i, int j) {
    return (ll)(sl[i].w + sr[j].w) * (min(sl[i].x, sr[j].x) + min(sl[i].y, sr[j].y));
}

bool inside(PT a, PT b) {
    return a.x <= b.x && a.y <= b.y;
}

void fix(int i, int f) {
    while (!a.empty() && (!f ? (a.back().y <= i) : (a.back().y >= i))) {
        a.pop_back();
    }
}

int bin(int i, int j, int f) {
    int l = 0, r = (int)sl.size() - 1, spl = (!f ? sl.size() : -1);
    while (l <= r) {
        int mid = (l + r) / 2;
        if (cost(mid, i) >= cost(mid, j)) {
            spl = mid;
            if (!f) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (!f) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return spl;
}

void add(int i, int j, int f) {
    if (a.empty()) {
        a.push_back(PT(i, !f ? INF : -INF));
    }
    if (cost(j, i) <= cost(j, a.back().x)) {
        return;
    }
    while (1) {
        int j = bin(a.back().x, i, f);
        if ((!f ? j >= a.back().y : j <= a.back().y)) {
            a.pop_back();
            continue;
        }
        a.push_back(PT(i, j));
        break;
    }
}

void solve() {
    b.clear();
    a.clear();
    int ql = sr.size(), qr = ql;
    b.push_back(ql);
    for (int i = 0; i < sl.size(); i++) {
        fix(i, false);
        while (ql && !inside(PT(sl[i].x, sl[i].y), PT(sr[ql - 1].x, sr[ql - 1].y))) {
            ql--;
            add(ql, i, false);
        }
        while (qr > ql && inside(PT(sr[qr - 1].x, sr[qr - 1].y), PT(sl[i].x, sl[i].y))) {
            if (qr <= b.back()) {
                b.push_back(ql);
                a.clear();
            }
            qr--;
        }
        if (!a.empty()) {
            int j = a.back().x;
            ans = max(ans, cost(i, j));
        }
    }
    while (qr > ql) {
        if (qr <= b.back()) {
            b.push_back(ql);
            a.clear();
        }
        qr--;
    }
    for (int i = (int)sl.size() - 1; i >= 0; i--) {
        fix(i, true);
        while (qr < sr.size() && !inside(PT(sr[qr].x, sr[qr].y), PT(sl[i].x, sl[i].y))) {
            if (qr >= b.back()) {
                b.pop_back();
                a.clear();
            }
            add(qr, i, true);
            qr++;
        }
        while (ql < qr && inside(PT(sl[i].x, sl[i].y), PT(sr[ql].x, sr[ql].y))) {
            ql++;
        }
        if (!a.empty()) {
            int j = a.back().x;
            ans = max(ans, cost(i, j));
        }
    }
    for (int i = (int)sl.size() - 1, j = -1; i >= 0; i--) {
        while (j + 1 < sr.size() && inside(PT(sl[i].x, sl[i].y), PT(sr[j + 1].x, sr[j + 1].y))) {
            j++;
        }
        if (j >= 0) {
            ans = max(ans, cost(i, j));
        }
    }
    for (int i = 0, j = sl.size(); i < sr.size(); i++) {
        while (j > 0 && inside(PT(sr[i].x, sr[i].y), PT(sl[j - 1].x, sl[j - 1].y))) {
            j--;
        }
        if (j < sl.size()) {
            ans = max(ans, cost(j, i));
        }
    }
}

void calcY(int l, int r, int xl, int xm, int xr, int yl, int yr) {
    if (l == r - 1) {
        ans = max(ans, (ll)max(ps[l].x - xl, xr - ps[l].x) * (yr - yl));
        ans = max(ans, (ll)(xr - xl) * max(ps[l].y - yl, yr - ps[l].y));
        return;
    }
    int mid = (l + r) / 2;
    int ym = ps[mid].y;
    calcY(l, mid, xl, xm, xr, yl, ym);
    calcY(mid, r, xl, xm, xr, ym, yr);
    sl.clear();
    sr.clear();
    int L = xl, R = xr;
    for (int i = mid - 1; i >= l; i--) {
        sl.push_back(Ival(ym - ps[i].y, xm - L, R - xm));
        if (ps[i].x <= xm) {
            L = max(L, ps[i].x);
        }
        if (ps[i].x >= xm) {
            R = min(R, ps[i].x);
        }
    }
    sl.push_back(Ival(ym - yl, xm - L, R - xm));
    reverse(sl.begin(), sl.end());
    L = xl;
    R = xr;
    for (int i = mid; i < r; i++) {
        sr.push_back(Ival(ps[i].y - ym, xm - L, R - xm));
        if (ps[i].x <= xm) {
            L = max(L, ps[i].x);
        }
        if (ps[i].x >= xm) {
            R = min(R, ps[i].x);
        }
    }
    sr.push_back(Ival(yr - ym, xm - L, R - xm));
    solve();
}

void calcX(int l, int r, int xl, int xr) {
    if (l == r - 1) {
        ans = max(ans, (ll)max(ps[l].x - xl, xr - ps[l].x) * H);
        ans = max(ans, (ll)(xr - xl) * max(ps[l].y, H - ps[l].y));
        return;
    }
    int mid = (l + r) / 2;
    int xm = ps[mid].x;
    calcX(l, mid, xl, xm);
    calcX(mid, r, xm, xr);
    for (int i = l; i < r; i++) {
        swap(ps[i].x, ps[i].y);
    }
    merge(ps + l, ps + mid, ps + mid, ps + r, tmp + l);
    for (int i = l; i < r; i++) {
        ps[i] = tmp[i];
        swap(ps[i].x, ps[i].y);
    }
    calcY(l, r, xl, xm, xr, 0, H);
}

int main() {
    IOS;
    int n;
    cin >> W >> H >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        ps[i] = PT(x, y);
    }
    sort(ps, ps + n);
    ans = max((ll)H, (ll)W);
    calcX(0, n, 0, W);
    cout << ans << endl;
    return 0;
}
