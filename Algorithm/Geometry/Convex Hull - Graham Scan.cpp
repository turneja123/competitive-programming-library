//https://cses.fi/problemset/task/2195/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
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
    vector<PT> hull = convex_hull(p, true);
    cout << hull.size() << endl;
    for (auto p : hull) {
        cout << p.x << " " << p.y << endl;
    }
    return 0;
}
