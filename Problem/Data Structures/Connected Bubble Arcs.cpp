//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

struct Node {
    int lazy;
    int mn;
    Node() {
        lazy = 0;
        mn = N;
    }
    Node(int x) {
        lazy = 0;
        mn = x;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.mn = min(left.mn, right.mn);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].mn += segtree[node].lazy;
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
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return N;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].mn;
    }
    int mid = (l + r) / 2;
    return min(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
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
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> v(n);
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        v[i] = {l, r};
        compr.push_back(l);
        compr.push_back(r);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    int m = compr.size();
    for (int i = 0; i < n; i++) {
        auto [l, r]  = v[i];
        l = lower_bound(compr.begin(), compr.end(), l) - compr.begin();
        r = lower_bound(compr.begin(), compr.end(), r) - compr.begin();
        v[i] = {2 * l, 2 * r};
    }
    multiset<int> st;
    build(0, 2 * m, 0);
    vector<int> f(n, 0);
    for (int i = 0; i < n; i++) {
        int j = i;
        auto [l, r] = v[j];
        incUpdate(0, 0, 2 * m, l, r, 1);
        st.insert(l);
        st.insert(r);
        f[j] = 1;
    }
    if (getSum(0, 2 * m, *st.begin(), *st.rbegin(), 0) > 0) {
        cout << "DA" << endl;
    } else {
        cout << "NE" << endl;
    }

    for (int i = 0; i < q; i++) {
        int j;
        cin >> j;
        j--;
        auto [l, r] = v[j];
        if (f[j]) {
            incUpdate(0, 0, 2 * m, l, r, -1);
            st.erase(st.find(l));
            st.erase(st.find(r));
            f[j] = 0;
        } else {
            incUpdate(0, 0, 2 * m, l, r, 1);
            st.insert(l);
            st.insert(r);
            f[j] = 1;
        }
        if (st.empty()) {
            cout << "DA" << endl;
            continue;
        }
        if (getSum(0, 2 * m, *st.begin(), *st.rbegin(), 0) > 0) {
            cout << "DA" << endl;
        } else {
            cout << "NE" << endl;
        }
    }


    return 0;
}
