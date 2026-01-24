//https://dmoj.ca/problem/dmopc19c7p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int SQ = 450;
const ll INF = 1e18;

struct PT {
    int x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    bool operator == (const PT &a) const { return x == a.x && y == a.y; }
    bool operator < (const PT &a) const { return x < a.x || (x == a.x && y < a.y); }
};

int orientation(PT &p1, PT &p2, PT &p3) {
    long long cross = (ll)(p2.x - p1.x) * (p3.y - p1.y) - (ll)(p2.y - p1.y) * (p3.x - p1.x);
    if (cross > 0) return 1; // ccw
    if (cross < 0) return -1; // cw
    return 0; // collinear
}

bool cw(PT &p1, PT &p2, PT &p3) {
    int o = orientation(p1, p2, p3);
    return o < 0;
}

void convex_hull(vector<PT> &p, vector<PT> &u) {
    u.clear();
    for (int i = 0; i < p.size(); i++) {
        while (u.size() >= 2 && cw(u[u.size() - 2], u.back(), p[i])) {
            u.pop_back();
        }
        u.push_back(p[i]);
    }
    return;
}

ll w;

int extreme(vector<PT> &p, PT v) {
    int l = 0, r = p.size() - 1;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        ll f1 = -((ll)v.x * p[m1].y - (ll)v.y * p[m1].x);
        ll f2 = -((ll)v.x * p[m2].y - (ll)v.y * p[m2].x);
        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }

    ll ans = INF;
    for (int i = l; i <= r; i++) {
        ans = min(ans, (ll)v.x * p[i].y - (ll)v.y * p[i].x);
    }
    return ans < w;
}

struct Block {
    int sz;
    vector<PT> hull;
    vector<PT> by_ord;
    vector<PT> by_x;

    Block() {
        sz = 0;
    }

    void insert(PT a) {
        int pos = sz;
        for (int i = 0; i < sz; i++) {
            ll val = (ll)a.x * by_ord[i].y - (ll)a.y * by_ord[i].x - w;
            if (val < 0) {
                pos = i;
                break;
            }
        }
        by_ord.insert(by_ord.begin() + pos, a);
        pos = lower_bound(by_x.begin(), by_x.end(), a) - by_x.begin();
        by_x.insert(by_x.begin() + pos, a);
        sz++;

        convex_hull(by_x, hull);
    }

    void build() {
        sz = by_ord.size();
        by_x = by_ord;
        sort(by_x.begin(), by_x.end());
        convex_hull(by_x, hull);
    }

    int query(PT a) {
        if (!sz) {
            return 0;
        }
        return extreme(hull, a);
    }

};

Block blocks[2 * SQ];
vector<int> block_ids;

int main() {
    IOS;
    int n, q, m = 0, tot = 0;
    cin >> n >> q >> w;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        queries.push_back({1, x, y});
    }
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "INSERT") {
            int x, y;
            cin >> x >> y;
            queries.push_back({1, x, y});
        } else {
            int k;
            cin >> k;
            queries.push_back({0, k, -1});
        }
    }
    block_ids.push_back(0);
    m++;

    for (int i = 0; i < queries.size(); i++) {
        auto [t, x, y] = queries[i];
        if (t == 1) {
            PT p = {x, y};
            int pos = m - 1;
            for (int j = 0; j < m; j++) {
                if (blocks[block_ids[j]].query(p)) {
                    pos = j;
                    break;
                }
            }
            int actual = block_ids[pos];
            blocks[actual].insert(p);
            if (blocks[actual].sz == 2 * SQ) {
                block_ids.insert(block_ids.begin() + pos + 1, m);
                vector<PT> l, r;
                for (int i = 0; i < 2 * SQ; i++) {
                    if (i < SQ) {
                        l.push_back(blocks[actual].by_ord[i]);
                    } else {
                        r.push_back(blocks[actual].by_ord[i]);
                    }
                }
                blocks[actual].by_ord = l;
                blocks[actual].build();
                blocks[m].by_ord = r;
                blocks[m].build();
                m++;
            }
            tot++;
        } else {
            int k = tot - x, i = 0;
            for (; i < m; i++) {
                if (k - blocks[block_ids[i]].sz >= 0) {
                    k -= blocks[block_ids[i]].sz;
                } else {
                    break;
                }
            }
            auto p = blocks[block_ids[i]].by_ord[k];
            cout << p.x << " " << p.y << endl;

        }

    }

    return 0;
}
