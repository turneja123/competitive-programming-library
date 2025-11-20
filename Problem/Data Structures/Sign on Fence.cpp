//https://codeforces.com/contest/484/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

struct Node {
    ll pref;
    ll suf;
    ll sum;
    ll val;
    int sentinel;
    Node()  {
        sentinel = 1;
    }
    Node(ll x) : pref(x), suf(x), sum(x), val(x), sentinel(0) {}
};

Node segtree[4 * N];
int a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = 0;
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    node.suf = max(right.suf, right.sum + left.suf);
    node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel;
        return sentinel;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return combine(query(l, mid, lq, rq, 2 * node + 1), query(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(-INF);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int ans[N];
vector<tuple<int, int, int, int, int>> queries;

bool comp(int &a, int &b) {
    return (get<0>(queries[a]) + get<1>(queries[a])) / 2 > (get<0>(queries[b]) + get<1>(queries[b])) / 2;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back({x, i});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int q;
    cin >> q;
    vector<int> ord;
    for (int i = 0; i < q; i++) {
        int l, r, w;
        cin >> l >> r >> w;
        l--, r--;
        queries.push_back(make_tuple(0, 1e9, l, r, w));
        ord.push_back(i);
    }
    while (ord.size()) {
        vector<int> ord_nx;
        sort(ord.begin(), ord.end(), comp);
        build(0, n - 1, 0);
        int j = 0;
        for (int i : ord) {
            auto [l, r, lq, rq, w] = queries[i];
            int mid = (l + r) / 2;
            while (j < n && a[j].first >= mid) {
                update(0, n - 1, a[j].second, 1, 0);
                j++;
            }
            Node node = query(0, n - 1, lq, rq, 0);
            if (node.val >= w) {
                ans[i] = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
            get<0>(queries[i]) = l;
            get<1>(queries[i]) = r;
            if (l <= r) {
                ord_nx.push_back(i);
            }
        }
        ord = ord_nx;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
