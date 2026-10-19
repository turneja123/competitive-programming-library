//https://qoj.ac/problem/1650
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 30;

const int INF = 2e9;

struct Node1 {
    pair<int, int> mn[K]; //najmanji koji ima bit k
    pair<int, int> mx[K]; //najveci koji nema bit k
    pair<int, int> mnn;
    pair<int, int> mxx;

    int sentinel;
    Node1() {
        sentinel = 1;
    }
    Node1(int x, int j) {
        sentinel = 0;
        for (int i = 0; i < K; i++) {
            mn[i] = {INF, -1};
            mx[i] = {-1, -1};
            int c = (1 << i) & x;
            if (c) {
                mn[i] = {x, j};
            } else {
                mx[i] = {x, j};
            }
        }
        mnn = {x, j};
        mxx = {x, j};
    }
};

struct Segtree1 {


    vector<Node1> nodes;
    vector<int> a;
    int n;

    Segtree1(vector<int> _a) {
        a = _a;
        n = a.size();
        nodes.resize(4 * n);
        build(0, n - 1, 0);
    }

    Node1 combine(Node1 left, Node1 right) {
        if (left.sentinel) {
            return right;
        }
        if (right.sentinel) {
            return left;
        }
        Node1 node = Node1();
        node.sentinel = 0;
        for (int i = 0; i < K; i++) {
            node.mn[i] = min(left.mn[i], right.mn[i]);
            node.mx[i] = max(left.mx[i], right.mx[i]);
        }
        node.mnn = min(left.mnn, right.mnn);
        node.mxx = max(left.mxx, right.mxx);

        return node;
    }

    Node1 query(int l, int r, int lq, int rq, int node) {
        if (l > rq || r < lq) {
            Node1 sentinel;
            return sentinel;
        }

        if (lq <= l && rq >= r) {
            return nodes[node];
        }

        int mid = (l + r) / 2;
        return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            nodes[node] = Node1(a[l], l);
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
    }

};

struct Node2 {
    int and_val;
    int or_val;
    int sentinel;
    int ct;
    Node2() {
        sentinel = 1;
    }
    Node2(int x, int f) {
        sentinel = 0;
        if (f == 0) {
            and_val = x;
            or_val = 0;
            ct = 1;
        } else {
            and_val = (1 << K) - 1;
            or_val = x;
            ct = 0;
        }
    }
};

struct Segtree2 {
    vector<Node2> nodes;
    vector<int> a;
    int n;

    Segtree2(vector<int> _a) {
        a = _a;
        n = a.size();
        nodes.resize(4 * n);
        build(0, n - 1, 0);
    }

    Node2 combine(Node2 left, Node2 right) {
        if (left.sentinel) {
            return right;
        }
        if (right.sentinel) {
            return left;
        }
        Node2 node = Node2();
        node.sentinel = 0;
        node.and_val = left.and_val & right.and_val;
        node.or_val = left.or_val | right.or_val;
        node.ct = left.ct + right.ct;

        return node;
    }

    Node2 query(int l, int r, int lq, int rq, int node) {
        if (l > rq || r < lq) {
            Node2 sentinel;
            return sentinel;
        }

        if (lq <= l && rq >= r) {
            return nodes[node];
        }

        int mid = (l + r) / 2;
        return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
    }

    void update(int l, int r, int ind, int node) {
        if (l == r) {
            nodes[node] = Node2(a[l], 1);
            return;
        }

        int mid = (l + r) / 2;
        if (ind >= l && ind <= mid) {
            update(l, mid, ind, 2 * node + 1);
        } else {
            update(mid + 1, r, ind, 2 * node + 2);
        }
        nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
    }


    void build(int l, int r, int node) {
        if (l > r) {
            return;
        }
        if (l == r) {
            nodes[node] = Node2(a[l], 0);
            return;
        }

        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
    }

};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<pair<int, int>> ord;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ord.push_back({a[i], i});
    }
    sort(ord.begin(), ord.end());
    Segtree1 seg1 = Segtree1(a);
    Segtree2 seg2 = Segtree2(a);

    vector<pair<int, int>> queries;
    vector<int> ans(q, 0);
    vector<tuple<int, int, int>> events;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries.push_back({l, r});
        Node1 node = seg1.query(0, n - 1, l, r, 0);
        for (int j = 0; j < K; j++) {
            if (node.mn[j].second != -1) {
                events.push_back({node.mn[j].first, node.mn[j].second, i});
            }
            if (node.mx[j].second != -1) {
                events.push_back({node.mx[j].first, node.mx[j].second - 1, i});
            }
        }
        events.push_back({node.mnn.first, node.mnn.second, i});
        events.push_back({node.mxx.first, node.mxx.second - 1, i});
    }
    sort(events.begin(), events.end());
    int ptr = 0;
    for (auto [x, y, j] : events) {
        pair<int, int> p = {x, y};
        while (ptr < n && ord[ptr] <= p) {
            int i = ord[ptr].second;
            seg2.update(0, n - 1, i, 0);
            ptr++;
        }
        auto [l, r] = queries[j];
        Node2 node = seg2.query(0, n - 1, l, r, 0);
        if (node.or_val == node.and_val && node.ct != 0 && node.ct != r - l + 1) {
            ans[j] = 1;
        }
    }
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
