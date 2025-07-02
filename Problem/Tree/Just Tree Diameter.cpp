//https://ocpc2025s.eolymp.space/en/compete/s47ok89k9t7evbt1ovdfvc933c/problem/5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct Line {
    long long k, y;
    long double xr = 1e18;
    Line(long long _k, long long _y) {
        k = _k;
        y = _y;
    }
    long long f(long long x) {
        return k * x + y;
    }
};

long double intersect(Line &p, Line &q) {
    return (long double)1.0 * (p.y - q.y) / (q.k - p.k);
}

struct CHT {
    vector<pair<ll, ll>> add;
    vector<Line> hull;
    void add_line(ll k, ll y) {
        add.push_back({k, y});
    }
    void build() {
        sort(add.begin(), add.end(), [](auto &p1, auto &p2){
            return p1.first < p2.first ||
                  (p1.first == p2.first && p1.second > p2.second);
        });
        vector<pair<ll, ll>> all;
        for (auto x : add) {
            if (all.empty() || all.back().first != x.first) {
                all.push_back(x);
            }
        }
        for (auto [k, y] : all) {
            Line cur(k, y);
            while (hull.size() >= 2 && intersect(hull[hull.size() - 2], hull.back()) >= intersect(hull.back(), cur)) {
                hull.pop_back();
            }
            hull.push_back(cur);
        }
        for (int i = 0; i < hull.size() - 1; i++) {
            hull[i].xr = intersect(hull[i], hull[i + 1]);
        }
    }

    long long query(long long x) {
        int l = 0, r = hull.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if ((long double)x < hull[mid].xr) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return hull[l].f(x);
    }

    void clear() {
        add.clear();
        hull.clear();
    }
};

CHT global;

void sum(vector<Line>& a, vector<Line>& b) {
    vector<pair<ll, ll>> add;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        add.emplace_back(a[i].k + b[j].k, a[i].y + b[j].y);
        if (a[i].xr <= b[j].xr) {
            i++;
        } else {
            j++;
        }
    }

    sort(add.begin(), add.end(), [](auto &p1, auto &p2){
        return p1.first < p2.first ||
              (p1.first == p2.first && p1.second > p2.second);
    });
    vector<pair<ll, ll>> all;
    for (auto x : add) {
        if (all.empty() || all.back().first != x.first) {
            all.push_back(x);
        }
    }
    vector<Line> hull;
    for (auto [k, y] : all) {
        Line cur(k, y);
        while (hull.size() >= 2 && intersect(hull[hull.size() - 2], hull.back()) >= intersect(hull.back(), cur)) {
            hull.pop_back();
        }
        hull.push_back(cur);
    }
    /*for (int i = 0; i < hull.size() - 1; i++) {
        hull[i].xr = intersect(hull[i], hull[i + 1]);
    }*/
    for (int i = 0; i < hull.size(); i++) {
        global.add_line(hull[i].k, hull[i].y);
    }

    return;
}

int sz[N];
bool seen_c[N];
int parent_c[N];
int mx[N];
long long best[N];
vector<pair<int, long long>> adj[N];

vector<Line> lines[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth1(int u, int p, int k, int cent) {
    mx[cent] = max(mx[cent], k);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth1(v, u, k + 1, cent);
        }
    }
    return;
}


void dfs_depth2(int u, int p, int k, long long y, int cent) {
    best[k] = max(best[k], y);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth2(v, u, k + 1, y + wt, cent);
        }
    }
    return;
}

void calc(int l, int r, vector<int> &childs) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    CHT lf;
    CHT rt;
    for (int i = l; i <= mid; i++) {
        int v = childs[i];
        for (int j = 0; j < lines[v].size(); j++) {
            lf.add_line(lines[v][j].k, lines[v][j].y);
        }
    }
    for (int i = mid + 1; i <= r; i++) {
        int v = childs[i];
        for (int j = 0; j < lines[v].size(); j++) {
            rt.add_line(lines[v][j].k, lines[v][j].y);
        }
    }
    lf.build();
    rt.build();
    sum(lf.hull, rt.hull);
    calc(l, mid, childs);
    calc(mid + 1, r, childs);
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    vector<int> childs;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            mx[v] = 0;
            dfs_depth1(v, v, 1, v);
            for (int i = 1; i <= mx[v]; i++) {
                best[i] = 0;
            }
            dfs_depth2(v, v, 1, wt, v);
            for (int i = 1; i <= mx[v]; i++) {
                lines[v].emplace_back(i, best[i]);
                global.add_line(i, best[i]);
            }
            childs.push_back(v);
        }
    }

    calc(0, childs.size() - 1, childs);

    for (auto v : childs) {
        lines[v].clear();
    }

    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    build(0, -1);
    long long sum = 0;

    global.build();
    cout << global.query(0) << endl;
    for (int i = 0; i < q; i++) {
        long long x;
        cin >> x;
        sum += x;
        cout << global.query(sum) << endl;
    }

    return 0;
}
