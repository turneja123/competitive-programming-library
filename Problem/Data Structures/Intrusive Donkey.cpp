//https://algotester.com/en/ArchiveProblem/DisplayWithEditor/71140
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18 + 1;

string s;

struct Node {
    long long val;
    long long ct;
    long long lazy;
    char c;
    Node() {
        ct = 0;
        lazy = 0;
        val = INF;
    }
    Node(long long _val, long long _ct, char _c) {
        val = _val;
        ct = _ct;
        lazy = 0;
        c = _c;
    }
};

Node segtree[4 * N];

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].val += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node].val = min(segtree[2 * node + 1].val, segtree[2 * node + 2].val);
}

void setUpdate(int node, int l, int r, int ind, long long val, long long ct) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val, ct, s[l]);
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(node * 2 + 1, l, mid, ind, val, ct);
    } else {
        setUpdate(node * 2 + 2, mid + 1, r, ind, val, ct);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node].val = min(segtree[2 * node + 1].val, segtree[2 * node + 2].val);
}


tuple<int, long long, long long> bound(int l, int r, int node, long long ind) {
    apply(node, l, r);
    if (l == r) {
        return make_tuple(l, segtree[node].val, segtree[node].ct);
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (segtree[2 * node + 2].val <= ind) {
        return bound(mid + 1, r, 2 * node + 2, ind);
    } else {
        return bound(l, mid, 2 * node + 1, ind);
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(l, 1, s[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node].val = min(segtree[2 * node + 1].val, segtree[2 * node + 2].val);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    cin >> s;
    s += 'a';
    build(0, n, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            long long l, r;
            cin >> l >> r;
            l--, r--;
            tuple<int, long long, long long> tup = bound(0, n, 0, l);
            vector<tuple<int, long long, long long>> v{tup};
            while (1) {
                auto [j, val, ct] = v.back();
                tuple<int, long long, long long> tup = bound(0, n, 0, val + ct);
                if (get<1>(tup) > r) {
                    break;
                }
                v.push_back(tup);
            }
            long long sum = 0;
            for (auto [j, val, ct] : v) {
                long long sz = ct;
                if (val < l) {
                    sz -= l - val;
                }
                if (val + ct - 1 > r) {
                    sz -= val + ct - 1 - r;
                }
                setUpdate(0, 0, n, j, val + sum, ct + sz);
                sum += sz;
            }
            incUpdate(0, 0, n, get<0>(v.back()) + 1, n, sum);
        } else {
            long long l;
            cin >> l;
            l--;
            tuple<int, long long, long long> tup = bound(0, n, 0, l);
            cout << s[get<0>(tup)] << endl;
        }
    }
    return 0;
}
