//https://cses.fi/problemset/task/2194/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll INF = 8e18;

struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
};

bool comp(PT &a, PT &b) {
    return a.x < b.x;
}

ll distsq(PT &a, PT &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ll sq(ll a) {
    if (a < 0) {
        return -INF;
    }
    return a * a;
}

pair<ll, vector<PT>> calc(int l, int r, vector<PT> &p) {

    if (l == r) {
        vector<PT> v{p[l]};
        return {INF, v};
    }
    int mid = (l + r) / 2;
    auto [bl, vlt] = calc(l, mid, p);
    auto [br, vrt] = calc(mid + 1, r, p);
    ll b = min(bl, br);
    ll spl = p[mid].x;
    vector<PT> vl, vr;
    for (PT &a : vlt) {
        if ((a.x - spl) * (a.x - spl) < b) {
            vl.push_back(a);
        }
    }
    for (PT &a : vrt) {
        if ((a.x - spl) * (a.x - spl) < b) {
            vr.push_back(a);
        }
    }

    int i = 0, j = 0;
    for (; i < vl.size(); i++) {
        while (j < vr.size() && sq(vl[i].y - vr[j].y) >= b) {
            j++;
        }
        for (int k = j; k < vr.size() && sq(vr[k].y - vl[i].y) < b; k++) {
            b = min(b, distsq(vl[i], vr[k]));
        }
    }
    vector<PT> v;
    i = 0, j = 0;
    while (i < vlt.size() && j < vrt.size()) {
        if (vlt[i].y < vrt[j].y) {
            v.push_back(vlt[i]);
            i++;
        } else {
            v.push_back(vrt[j]);
            j++;
        }
    }
    while (i < vlt.size()) {
        v.push_back(vlt[i]);
        i++;
    }
    while (j < vrt.size()) {
        v.push_back(vrt[j]);
        j++;
    }
    vl.clear(), vr.clear();
    vlt.clear(), vrt.clear();
    return {b, v};
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<PT> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }
    sort(p.begin(), p.end(), comp);
    auto [ans, _] = calc(0, n - 1, p);
    cout << ans;

    return 0;
}
