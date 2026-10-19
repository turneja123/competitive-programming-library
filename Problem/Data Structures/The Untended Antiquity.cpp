//https://codeforces.com/contest/869/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ull = unsigned long long;

const int N = 2505;

struct BIT {
    vector<ull> t_fi;
    vector<ull> t_se;
    int n;

    BIT() {

    }

    BIT(int _n) {
        n = _n;
        t_fi.resize(n);
        t_se.resize(n);
    }

    void upd(int i, ull fi, ull se) {
        i++;
        for (; i <= n; i += i & (-i)) {
            t_fi[i - 1] ^= fi;
            t_se[i - 1] ^= se;
        }
    }

    pair<ull, ull> query(int i) {
        i++;
        ull fi = 0, se = 0;
        for (; i >= 1; i -= i & (-i)) {
            fi ^= t_fi[i - 1];
            se ^= t_se[i - 1];
        }
        return {fi, se};
    }
};

BIT segtree[4 * N];

void query(int l, int r, int node, int x, int y, pair<ull, ull> &ans) {
    pair<ull, ull> cur = segtree[node].query(y);
    ans.first ^= cur.first;
    ans.second ^= cur.second;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) {
        query(l, mid, 2 * node + 1, x, y, ans);
    } else {
        query(mid + 1, r, 2 * node + 2, x, y, ans);
    }

}

void upd(int l, int r, int node, int lq, int rq, int ly, int ry, ull fi, ull se) {
    if (l > rq || r < lq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].upd(ly, fi, se);
        segtree[node].upd(ry + 1, fi, se);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, 2 * node + 1, lq, rq, ly, ry, fi, se);
    upd(mid + 1, r, 2 * node + 2, lq, rq, ly, ry, fi, se);
}

void build(int l, int r, int node, int n) {
    segtree[node] = BIT(n);
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
}

mt19937_64 gene(3);

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    n = max(n, m);
    m = max(n, m);
    build(0, n - 1, 0, n);
    map<tuple<int, int, int, int>, pair<ull, ull>> mp;
    for (int i = 0; i < q; i++) {
        int t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        if (t == 1) {
            ull h1 = gene(), h2 = gene();
            mp[make_tuple(x1, y1, x2, y2)] = {h1, h2};
            upd(0, n - 1, 0, x1, x2, y1, y2, h1, h2);
        } else if (t == 2) {
            auto it = mp.find({x1, y1, x2, y2});
            upd(0, n - 1, 0, x1, x2, y1, y2, it->second.first, it->second.second);
            mp.erase(it);
        } else {
            pair<ull, ull> h1 = {0, 0}, h2 = {0, 0};
            query(0, n - 1, 0, x1, y1, h1);
            query(0, n - 1, 0, x2, y2, h2);
            if (h1 == h2) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}
