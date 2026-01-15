//https://dmoj.ca/problem/mmm14g
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int SQ = 800;
const int W = (SQ + 63) / 64;

struct BIT {
    int n;
    vector<int> t;
    BIT() {
        n = 0;
    }
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
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
        if (t.empty()) {
            return 0;
        }
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return query(r) - query(l - 1);
    }
};

struct Node {
    BIT bit;
    vector<int> pos;
    vector<int> t;
    int n;

    Node() {}
};

Node segtree[4 * N];

void update_init(int l, int r, int ind, int val, int f, int node) {
    segtree[node].pos.push_back(val);
    if (f) {
        segtree[node].t.push_back(val);
    }

    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update_init(l, mid, ind, val, f, 2 * node + 1);
    } else {
        update_init(mid + 1, r, ind, val, f, 2 * node + 2);
    }
}

void update(int l, int r, int ind, int val, int add, int node) {
    int j = lower_bound(segtree[node].pos.begin(), segtree[node].pos.end(), val) - segtree[node].pos.begin();
    segtree[node].bit.upd(j + 1, add);

    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, add, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, add, 2 * node + 2);
    }
}

void build(int l, int r, int node) {
    if (!segtree[node].pos.empty()) {
        sort(segtree[node].pos.begin(), segtree[node].pos.end());
        sort(segtree[node].t.begin(), segtree[node].t.end());
        segtree[node].pos.erase(unique(segtree[node].pos.begin(), segtree[node].pos.end()), segtree[node].pos.end());
        int n = segtree[node].pos.size();
        vector<int> bi(n, 0);

        for (int i = 0, j = 0; i < segtree[node].t.size(); i++) {
            while (segtree[node].pos[j] != segtree[node].t[i]) {
                j++;
            }
            bi[j] = 1;
        }


        segtree[node].n = n;
        segtree[node].bit = BIT(segtree[node].n, bi);
    }

    if (l == r) {
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
}


int query(int l, int r, int lq1, int rq1, int lq2, int rq2, int k, int node) {

    if (l == r) {
        return l;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1].pos.empty()) {
        return query(mid + 1, r, lq1, rq1, lq2, rq2, k, 2 * node + 2);
    }
    int ans = 0;
    int p1 = lower_bound(segtree[2 * node + 1].pos.begin(), segtree[2 * node + 1].pos.end(), lq1) - segtree[2 * node + 1].pos.begin();
    int p2 = upper_bound(segtree[2 * node + 1].pos.begin(), segtree[2 * node + 1].pos.end(), rq1) - segtree[2 * node + 1].pos.begin() - 1;
    ans += segtree[2 * node + 1].bit.query(p1 + 1, p2 + 1);

    if (lq2 != -1) {
        p1 = lower_bound(segtree[2 * node + 1].pos.begin(), segtree[2 * node + 1].pos.end(), lq2) - segtree[2 * node + 1].pos.begin();
        p2 = upper_bound(segtree[2 * node + 1].pos.begin(), segtree[2 * node + 1].pos.end(), rq2) - segtree[2 * node + 1].pos.begin() - 1;
        ans += segtree[2 * node + 1].bit.query(p1 + 1, p2 + 1);
    }
    if (ans < k) {
        return query(mid + 1, r, lq1, rq1, lq2, rq2, k - ans, 2 * node + 2);
    } else {
        return query(l, mid, lq1, rq1, lq2, rq2, k, 2 * node + 1);
    }

}


struct alignas(32) Block {
    int n;
    int laz;
    vector<tuple<int, int, int>> v;
    vector<pair<int, int>> by_a;
    vector<pair<int, int>> by_b;
    vector<int> id_a, id_b;

    vector<int> a, b;
    vector<ll> pref;

    Block() {

    }

    Block(int _n) {
        n = _n;
        v.resize(n);
        by_a.resize(n);
        by_b.resize(n);
        a.resize(n);
        b.resize(n);
        id_a.resize(n);
        id_b.resize(n);
    }

    void build() {
        if (n != SQ) {
            return;
        }

        sort(v.begin(), v.end());
        for (int i = 0; i < n; i++) {
            auto [A, I, B] = v[i];
            by_a[i] = {A, I};
            by_b[i] = {B, I};
            id_a[I] = i;
            a[i] = A;
        }
        sort(by_b.begin(), by_b.end());
        for (int i = 0; i < n; i++) {
            auto [B, I] = by_b[i];
            id_b[I] = i;
            b[i] = B;
        }

        pref.assign((n + 1) * W, 0);
        for(int i = 0; i < n; i++){
            memcpy(&pref[(i + 1) * W], &pref[i * W], W * sizeof(ll));
            int p = id_b[by_a[i].second];
            pref[(i + 1) * W + (p >> 6)] |= 1LL << (p & 63);
        }
    }

    void upd(int j, int nw_a, int nw_b) {
        if (n != SQ) {
            return;
        }
        int olda = a[id_a[j]];
        int oldb = b[id_b[j]];

        int ia = id_a[j];
        by_a.erase(by_a.begin() + ia);
        auto pos_a = lower_bound(by_a.begin(), by_a.end(), make_pair(nw_a, j));
        by_a.insert(pos_a, make_pair(nw_a, j));

        int ib = id_b[j];
        by_b.erase(by_b.begin() + ib);
        auto pos_b = lower_bound(by_b.begin(), by_b.end(), make_pair(nw_b, j));
        by_b.insert(pos_b, make_pair(nw_b, j));

        for (int i = 0; i < n; i++) {
            id_a[by_a[i].second] = i;
            id_b[by_b[i].second] = i;
            a[i] = by_a[i].first;
            b[i] = by_b[i].first;
        }

        pref.assign((n + 1) * W, 0);
        for(int i = 0; i < n; i++){
            memcpy(&pref[(i + 1) * W], &pref[i * W], W * sizeof(ll));
            int p = id_b[by_a[i].second];
            pref[(i + 1) * W + (p >> 6)] |= 1LL << (p & 63);
        }
    }


    int query(int l, int r) {
        int ans = 0;
        int L = upper_bound(a.begin(), a.end(), r) - a.begin() - 1;
        if (L >= 0) {
            int R = lower_bound(b.begin(), b.end(), l) - b.begin();
            if (R <= n - 1) {
                const ll* p = &pref[(L + 1) * W];
                int sw = R >> 6;
                int sb = R & 63;

                if (sw < W) {
                    ans += __builtin_popcountll(p[sw] & (~0ULL << sb));
                }
                for(int w = sw + 1; w < W; ++w) {
                    ans += __builtin_popcountll(p[w]);
                }
            }
        }

        return ans;

    }

};

Block b[N / SQ + 5];
int A[N], B[N];

int query(int l, int r, int L, int R) {

    int ans = 0;

    if (l / SQ == r / SQ) {
        for (int i = l; i <= r; i++) {
            if (A[i] <= R && B[i] >= L) {
                ans++;
            }
        }
        return ans;
    }
    int lbl = l / SQ;
    if (l % SQ != 0) {
        lbl++;
    }
    int rbl = r / SQ;
    if ((r + 1) % SQ != 0) {
        rbl--;
    }
    for (int i = lbl; i <= rbl; i++) {
        ans += b[i].query(L, R);
    }
    for (int i = l; i < lbl * SQ; i++) {
        if (A[i] <= R && B[i] >= L) {
            ans++;
        }
    }
    for (int i = (rbl + 1) * SQ; i <= r; i++) {
        if (A[i] <= R && B[i] >= L) {
            ans++;
        }
    }
    return ans;


}

int main() {
    IOS;
    int n, m, t, x, y, z;
    cin >> n >> m >> t >> x >> y >> z;
    for (int i = 0; i * SQ < n; i++) {
        int sz = min((i + 1) * SQ, n) - i * SQ;
        b[i] = Block(sz);
    }

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        b[i / SQ].v[i % SQ] = {l, i % SQ, r};
        A[i] = l, B[i] = r;
        update_init(0, N / 2 - 1, A[i], i, 1, 0);
    }
    for (int i = 0; i * SQ < n; i++) {
        b[i].build();
    }
    vector<tuple<int, int, int, int, int>> queries;

    for (int i = 0; i < m; i++) {
        int ti;
        cin >> ti;
        if (ti == 1) {
            int l, r, lo, hi;
            cin >> l >> r >> lo >> hi;
            queries.push_back(make_tuple(ti, l, r, lo, hi));


        } else if (ti == 2) {
            int j, lo, hi;
            cin >> j >> lo >> hi;
            j--;
            update_init(0, N / 2 - 1, lo, j, 0, 0);
            queries.push_back(make_tuple(ti, j, lo, hi, -1));

        } else {
            int l, r, k;
            cin >> l >> r >> k;
            queries.push_back(make_tuple(ti, l, r, k, -1));
        }
    }
    build(0, N / 2 - 1, 0);

    for (int i = 0; i < m; i++) {
        if (get<0>(queries[i]) == 1) {
            auto [ti, l, r, lo, hi] = queries[i];
            lo = t - lo, hi = t + hi;
            l--, r--;
            int ans;
            if (l <= r) {
                ans = query(l, r, lo, hi);
            } else {
                ans = query(0, r, lo, hi) + query(l, n - 1, lo, hi);
            }
            cout << ans << endl;
            t =  (t * x + ans * y) % z + 1;

        } else if (get<0>(queries[i]) == 2) {
            auto [ti, j, lo, hi, _] = queries[i];
            b[j / SQ].upd(j % SQ, lo, hi);
            update(0, N / 2 - 1, A[j], j, -1, 0);
            A[j] = lo;
            B[j] = hi;
            update(0, N / 2 - 1, A[j], j, 1, 0);

        } else {
            auto [ti, l, r, k, _] = queries[i];
            l--, r--;
            int d = r - l + 1;
            int lq1 = l, rq1 = r, lq2 = -1, rq2 = -1;

            if (r < l) {
                d = r + 1 + (n - l);
                lq1 = 0, rq1 = r;
                lq2 = l, rq2 = N / 2 - 1;
            }
            if (d < k) {
                cout << -1 << endl;
                continue;
            }
            cout << query(0, N / 2 - 1, lq1, rq1, lq2, rq2, k, 0) << endl;


        }
    }
    return 0;
}
