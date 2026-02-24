//https://codeforces.com/contest/453/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 2e9;

int S[N], M[N], R[N];

struct Item {
    int s;
    int m;
    int r;
    int t;
    Item(int _s, int _m, int _r) {
        s = _s, m = _m, r = _r;
        t = (r == 0 ? INF : (m + r - 1) / r);
    }
    bool operator < (const Item &a) const { return t < a.t; }
};

struct Node {
    int original;
    int uniform;
    int t;
    int lazy;
    vector<Item> items;
    vector<ll> pref_m;
    vector<ll> suf_r;

    Node() {
        lazy = -1;
    }
};

int a[N];
Node segtree[4 * N];

void combine(Node &left, Node &right, Node &node) {
    node.original = 0;
    node.uniform = 1;
    node.t = left.t;
    if (left.t != right.t || !left.uniform || !right.uniform || left.original || right.original) {
        node.uniform = 0;
    }
    return;
}

void compose(int parent, int child) {
    segtree[child].lazy = segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy == -1) {
        return;
    }
    segtree[node].t = segtree[node].lazy;
    segtree[node].uniform = 1;
    segtree[node].original = 0;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = -1;
}


ll setUpdate(int node, int l, int r, int lq, int rq, ll val) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq && segtree[node].uniform) {
        if (segtree[node].original) {
            ll cur = segtree[node].items[0].s;
            cur = min((ll)segtree[node].items[0].m, cur + val * segtree[node].items[0].r);
            segtree[node].original = 0;
            segtree[node].t = val;
            return cur;
        }
        ll tim = val - segtree[node].t;
        ll ans = 0;
        Item item = Item(-1, -1, -1);
        item.t = tim;
        int j = upper_bound(segtree[node].items.begin(), segtree[node].items.end(), item) - segtree[node].items.begin();
        if (j - 1 >= 0) {
            ans += segtree[node].pref_m[j - 1];
        }
        if (j != segtree[node].items.size()) {
            ans += segtree[node].suf_r[j] * tim;
        }
        segtree[node].lazy = val;
        return ans;
    }
    ll ans = 0;
    int mid = (l + r) / 2;
    ans += setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    ans += setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);

    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    combine(segtree[2 * node + 1], segtree[2 * node + 2], segtree[node]);
    return ans;
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    segtree[node].t = 0;
    if (l == r) {
        segtree[node].uniform = 1;
        segtree[node].original = 1;
        segtree[node].items = {Item(S[l], M[l], R[l])};
        segtree[node].pref_m = {M[l]};
        segtree[node].suf_r = {R[l]};

        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node].uniform = 0;
    segtree[node].original = 0;
    int i = 0, j = 0;
    while (i < segtree[2 * node + 1].items.size() && j < segtree[2 * node + 2].items.size()) {
        if (segtree[2 * node + 1].items[i] < segtree[2 * node + 2].items[j]) {
            segtree[node].items.push_back(segtree[2 * node + 1].items[i++]);
        } else {
            segtree[node].items.push_back(segtree[2 * node + 2].items[j++]);
        }
    }
    while (i < segtree[2 * node + 1].items.size()) {
        segtree[node].items.push_back(segtree[2 * node + 1].items[i++]);
    }
    while (j < segtree[2 * node + 2].items.size()) {
        segtree[node].items.push_back(segtree[2 * node + 2].items[j++]);
    }
    int n = segtree[node].items.size();
    segtree[node].pref_m.resize(n);
    segtree[node].suf_r.resize(n);
    for (int i = 0; i < n; i++) {
        segtree[node].pref_m[i] = (i == 0 ? 0 : segtree[node].pref_m[i - 1]) + segtree[node].items[i].m;
    }
    for (int i = n - 1; i >= 0; i--) {
        segtree[node].suf_r[i] = (i == n - 1 ? 0 : segtree[node].suf_r[i + 1]) + segtree[node].items[i].r;
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i] >> M[i] >> R[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        cout << setUpdate(0, 0, n - 1, l, r, t) << endl;
    }

    return 0;
}
