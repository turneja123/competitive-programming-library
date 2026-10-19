//bbc18q
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9 + 1;

struct Node {
    int lazy;
    int val;
    Node() {
        lazy = INF;
        val = INF;
    }
    Node(int x) {
        lazy = INF;
        val = x;
    }
};

int a[N];
Node segtree[4 * N];


void compose(int parent, int child) {
    segtree[child].lazy = min(segtree[child].lazy, segtree[parent].lazy);
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy == INF) {
        return;
    }
    segtree[node].val = min(segtree[node].val, segtree[node].lazy);
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = INF;
}

void setUpdate(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = min(segtree[node].lazy , add);
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, add);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
}

int getSum(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return getSum(l, mid, ind, 2 * node + 1);
    } else {
        return getSum(mid + 1, r, ind, 2 * node + 2);
    }
}

void upd(int l, int r, int ind, int val, int node) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(l, mid, ind, val, 2 * node + 1);
    } else {
        upd(mid + 1, r, ind, val, 2 * node + 2);
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);

}

struct BIT {
    int n;
    vector<ll> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, ll val) {
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    ll query(int i) {
        i++;
        ll ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


int main() {
    IOS;
    int n, q;
    cin >> n;
    map<int, int> mp;
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
        compr.push_back(a[i]);
    }
    build(0, n - 1, 0);
    cin >> q;
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int h;
            cin >> h;
            compr.push_back(h);
            queries.push_back({h, -1});
        } else {
            int h, j;
            cin >> j >> h;
            j--;
            compr.push_back(h);
            queries.push_back({h, j});
        }
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    auto id = [&](int x) -> int {
        return lower_bound(compr.begin(), compr.end(), x) - compr.begin();
    };
    int m = compr.size();
    BIT bit_ct(m), bit_sum(m);
    for (int i = 0; i < n; i++) {
        bit_ct.upd(id(a[i]), 1);
        bit_sum.upd(id(a[i]), a[i]);
    }

    auto get_v = [&](int cur) -> ll {
        ll ans = bit_ct.query(id(cur)) * cur - bit_sum.query(id(cur));
        return ans;
    };
    for (int i = 0; i < q; i++) {
        auto [h, j] = queries[i];
        if (j == -1) {
            setUpdate(0, 0, n - 1, 0, n - 1, h);
            ll ansZ = 0;
            while (1) {
                auto it = mp.end();
                it--;
                if (it->first <= h) {
                    break;
                }
                ansZ += (ll)it->second * (it->first - h);
                bit_ct.upd(id(it->first), -it->second);
                bit_sum.upd(id(it->first), (ll)-it->second * it->first);

                bit_ct.upd(id(h), it->second);
                bit_sum.upd(id(h), (ll)it->second * h);
                mp[h] += it->second;
                mp.erase(it);
            }
            cout << ansZ << " " << get_v(h) << endl;
        } else {
            int val = getSum(0, n - 1, j, 0);
            auto it = mp.find(val);
            it->second--;
            if (it->second == 0) {
                mp.erase(it);
            }
            mp[h]++;
            upd(0, n - 1, j, h, 0);
            bit_ct.upd(id(val), -1);
            bit_sum.upd(id(val), -val);


            bit_ct.upd(id(h), 1);
            bit_sum.upd(id(h), h);
        }
    }

    return 0;
}
