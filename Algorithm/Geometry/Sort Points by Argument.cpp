//https://judge.yosupo.jp/problem/sort_points_by_argument
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

const int INF = 1e9 + 1;

PT p0 = PT(0, 0);

int sign(ll x) {
    return (x > 0) - (x < 0);
}

ll cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

ll orientation (PT a, PT b, PT c) {
    return sign(cross(b - a, c - a));
}

ll distsq(PT a, PT b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int half(PT a) {
    return a.y < 0 || (a.y == 0 && a.x > 0);
}

bool comp(PT a, PT b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) {
        return ha > hb;
    }
    int o = orientation(p0, a, b);
    if (o == 1) {
        return 1;
    }
    if (o == -1) {
        return 0;
    }
    return distsq(p0, a) < distsq(p0, b);
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = PT(x, y);
    }
    sort(p.begin(), p.end(), comp);
    for (int i = 0; i < n; i++) {
        cout << p[i].x << " " << p[i].y << endl;
    }

    return 0;
}
