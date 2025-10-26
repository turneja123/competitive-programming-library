//https://cses.fi/problemset/task/1742/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct P {
    ll x, y;
};

int sgn(__int128 v) {
    return (v > 0) - (v < 0);
}

int orient(const P& a, const P& b, const P& c) {
    __int128 x1 = b.x - a.x, y1 = b.y - a.y;
    __int128 x2 = c.x - a.x, y2 = c.y - a.y;
    return sgn(x1 * y2 - y1 * x2);
}

bool onSeg(const P& a, const P& b, const P& c) {
    if (orient(a, b, c) != 0) return false;
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}

bool intersect(const P& a, const P& b, const P& c, const P& d) {
    int o1 = orient(a, b, c), o2 = orient(a, b, d);
    int o3 = orient(c, d, a), o4 = orient(c, d, b);

    if (o1 == 0 && onSeg(a, b, c)) return true;
    if (o2 == 0 && onSeg(a, b, d)) return true;
    if (o3 == 0 && onSeg(c, d, a)) return true;
    if (o4 == 0 && onSeg(c, d, b)) return true;

    return (o1 * o2 < 0 && o3 * o4 < 0);
}

pair<P, P> seg[N];
pair<P, P> seg_compr[N];

char c[N];
int d[N];
ll pref[N];

vector<pair<int, int>> hori[N];
vector<pair<int, int>> vert[N];

int id(ll x, vector<ll> &sorted) {
    return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
}



int main() {
    IOS;
    int n;
    cin >> n;
    P p{0, 0};
    vector<ll> sortedx{0}, sortedy{0};
    for (int i = 0; i < n; i++) {
        P nx = p;
        cin >> c[i] >> d[i];
        if (c[i] == 'U') {
            nx.y += d[i];
        } else if (c[i] == 'D') {
            nx.y -= d[i];
        } else if (c[i] == 'R') {
            nx.x += d[i];
        } else {
            nx.x -= d[i];
        }
        sortedx.push_back(nx.x);
        sortedy.push_back(nx.y);
        seg[i] = {p, nx};
        p = nx;
        pref[i] = (i == 0 ? 0 : pref[i - 1]) + d[i];
    }
    sort(sortedx.begin(), sortedx.end());
    sortedx.erase(unique(sortedx.begin(), sortedx.end()), sortedx.end());
    sort(sortedy.begin(), sortedy.end());
    sortedy.erase(unique(sortedy.begin(), sortedy.end()), sortedy.end());
    int X = sortedx.size(), Y = sortedy.size();
    for (int i = 0; i < n; i++) {
        seg_compr[i].first = P{id(seg[i].first.x, sortedx), id(seg[i].first.y, sortedy)};
        seg_compr[i].second = P{id(seg[i].second.x, sortedx), id(seg[i].second.y, sortedy)};
    }
    int l = 0, r = n - 1, spl = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        vector<tuple<int, int, int, int>> event;
        for (int i = 0; i <= mid; i++) {
            auto [a, b] = seg_compr[i];
            if (a.x == b.x) {
                int l = min(a.y, b.y), r = max(a.y, b.y);
                vert[a.x].push_back({l, 1});
                vert[a.x].push_back({r + 1, -1});
                event.push_back(make_tuple(a.x, 1, l, r));

            } else {
                int l = min(a.x, b.x), r = max(a.x, b.x);
                hori[a.y].push_back({l, 1});
                hori[a.y].push_back({r + 1, -1});
                event.push_back(make_tuple(l, -1, a.y, 1));
                event.push_back(make_tuple(r + 1, -1, a.y, -1));
            }
        }
        ll s = 0;
        for (int i = 0; i < X; i++) {
            if (vert[i].empty()) {
                continue;
            }
            sort(vert[i].begin(), vert[i].end());
            int last = vert[i][0].first, ct = 0;
            for (auto [x, d] : vert[i]) {
                s += (ll)(x - last) * ct * (ct - 1) / 2;
                ct += d;
                last = x;
            }
            vert[i].clear();
        }
        for (int i = 0; i < Y; i++) {
            if (hori[i].empty()) {
                continue;
            }
            sort(hori[i].begin(), hori[i].end());
            int last = hori[i][0].first, ct = 0;
            for (auto [x, d] : hori[i]) {
                s += (ll)(x - last) * ct * (ct - 1) / 2;
                ct += d;
                last = x;
            }
            hori[i].clear();
        }
        BIT bit(Y);
        sort(event.begin(), event.end());

        for (auto [x, t, l, r] : event) {
            if (t == -1) {
                bit.upd(l + 1, r);
            } else {
                s += bit.query(l + 1, r + 1);
            }

            if (s > mid) {
                break;
            }
        }
        if (s <= mid) {
            spl = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (spl == n - 1) {
        cout << pref[n - 1];
        return 0;
    }
    int j = spl + 1;
    if (c[j - 1] == 'R' && c[j] == 'L') {
        cout << pref[j - 1];
        return 0;
    }
    if (c[j - 1] == 'L' && c[j] == 'R') {
        cout << pref[j - 1];
        return 0;
    }
    if (c[j - 1] == 'U' && c[j] == 'D') {
        cout << pref[j - 1];
        return 0;
    }
    if (c[j - 1] == 'D' && c[j] == 'U') {
        cout << pref[j - 1];
        return 0;
    }

    l = 1, r = d[j], spl = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        P p = seg[j].first;
        P nx = p;
        if (c[j] == 'U') {
            nx.y += mid;
        } else if (c[j] == 'D') {
            nx.y -= mid;
        } else if (c[j] == 'R') {
            nx.x += mid;
        } else {
            nx.x -= mid;
        }
        int can = 0;
        for (int i = 0; i < j - 1; i++) {
            if (intersect(seg[i].first, seg[i].second, p, nx)) {
                can = 1;
            }
        }

        if (can) {
            spl = mid;
            r = mid - 1;
        } else {
            l = mid + 1;

        }
    }
    ll ans = pref[j - 1] + spl;
    cout << ans;

    return 0;
}
