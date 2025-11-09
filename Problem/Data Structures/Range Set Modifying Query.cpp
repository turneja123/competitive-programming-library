//https://atcoder.jp/contests/abc430/tasks/abc430_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

struct Node {
    int lazy;
    int mx;
    int ct;
    Node() {
        lazy = 0;
    }
    Node(int x) {
        ct = 1;
        mx = x;
        lazy = 0;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.mx > right.mx) {
        node.mx = left.mx;
        node.ct = left.ct;
    } else if (left.mx < right.mx) {
        node.mx = right.mx;
        node.ct = right.ct;
    } else {
        node.mx = right.mx;
        node.ct = left.ct + right.ct;
    }
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].mx += segtree[node].lazy;
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

Node getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node node(-N);
        return node;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
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


set<pair<int, int>> ivals[N];

void interval_insert(int l, int r, int j) {
    if (ivals[j].empty()) {
        ivals[j].insert(make_pair(l, r));
        incUpdate(0, 0, N - 1, l, r, 1);
        return;
    }
    auto it = ivals[j].lower_bound({l, r});
    if (it != ivals[j].begin()) {
        --it;
        if (it->second < l - 1) {
            ++it;
        }
    }
    int new_l = l;
    int new_r = r;
    while (it != ivals[j].end() && it->first <= r + 1) {
        new_l = min(new_l, it->first);
        new_r = max(new_r, it->second);
        incUpdate(0, 0, N - 1, it->first, it->second, -1);
        it = ivals[j].erase(it);
    }
    ivals[j].insert(make_pair(new_l, new_r));
    incUpdate(0, 0, N - 1, new_l, new_r, 1);
    return;
}

void interval_erase(int l, int r, int j) {
    if (ivals[j].empty()) {
        return;
    }
    auto it = ivals[j].lower_bound({l, r});
    if (it != ivals[j].begin()) {
        --it;
        if (it->second < l) {
            ++it;
        }
    }
    while (it != ivals[j].end() && it->first <= r) {
        int a = it->first;
        int b = it->second;
        incUpdate(0, 0, N - 1, a, b, -1);
        it = ivals[j].erase(it);
        if (a < l) {
            ivals[j].insert(make_pair(a, l - 1));
            incUpdate(0, 0, N - 1, a, l - 1, 1);
        }
        if (r < b) {
            ivals[j].insert(make_pair(r + 1, b));
            incUpdate(0, 0, N - 1, r + 1, b, 1);
            break;
        }
    }
    return;
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    build(0, N - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            int x;
            cin >> x;
            interval_insert(l, r, x);
        } else if (t == 2) {
            int x;
            cin >> x;
            interval_erase(l, r, x);
        } else {
            Node node = getSum(0, N - 1, l, r, 0);
            cout << node.mx << " " << node.ct << endl;
        }
    }




    return 0;
}
