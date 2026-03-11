//https://www.spoj.com/problems/INTDSET/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int M = 1e9 + 7;

vector<int> add[N];
vector<int> rem[N];

struct Node {
    ll sum;
    ll lazy;
    Node() {
        lazy = 1;
        sum = 0;
    }
    Node(ll x) {
        lazy = 1;
        sum = x;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = (left.sum + right.sum) % M;
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy = segtree[child].lazy * segtree[parent].lazy % M;

}

void apply(int node, int l, int r) {
    segtree[node].sum = segtree[node].sum * segtree[node].lazy % M;;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 1;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = segtree[node].lazy * add % M;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void setUpdate(int node, int l, int r, int ind, ll val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node].sum = (segtree[node].sum + val) % M;
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(node * 2 + 1, l, mid, ind, val);
    } else {
        setUpdate(node * 2 + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

long long getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return (getSum(l, mid, lq, rq, 2 * node + 1) + getSum(mid + 1, r, lq, rq, 2 * node + 2)) % M;
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(0);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);
        vector<int> compr;
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            compr.push_back(l);
            compr.push_back(r);
            a[i] = {l, r};
        }
        sort(compr.begin(), compr.end());
        compr.erase(unique(compr.begin(), compr.end()), compr.end());
        auto id = [&](int x) {
            return lower_bound(compr.begin(), compr.end(), x) - compr.begin() + 1;
        };

        for (int i = 0; i < n; i++) {
            a[i].first = id(a[i].first);
            a[i].second = id(a[i].second);
            auto [l, r] = a[i];
            add[l].push_back(r);
            rem[r + 1].push_back(l);
        }
        int m = compr.size();
        build(0, m, 0);
        setUpdate(0, 0, m, 0, 1);
        int j = 0;
        for (int i = 0; i <= m + 1; i++) {
            for (int l : rem[i]) {
                j = max(j, l);
            }
            for (int r : add[i]) {
                if (r < m) {
                    incUpdate(0, 0, m, r + 1, m, 2);
                }
                ll s = getSum(0, m, j, r, 0);
                setUpdate(0, 0, m, r, s);
            }
        }
        cout << getSum(0, m, j, m, 0) << endl;
        for (int i = 0; i <= m + 1; i++) {
            add[i].clear();
            rem[i].clear();
        }


    }

    return 0;
}
