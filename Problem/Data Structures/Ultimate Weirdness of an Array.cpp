//https://codeforces.com/contest/672/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

vector<int> divs[N];
vector<int> pos[N];
vector<pair<int, int>> upd[N];

struct Node {
    ll sum;
    int mn1;
    int mn2;
    int mnc;
    Node() : sum(0), mn1(0), mn2(0), mnc(0) {}
    Node(int x) : sum(x), mn1(x), mn2(INF), mnc(1) {}
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = left.sum + right.sum;
    if (left.mn1 == right.mn1) {
        node.mn1 = left.mn1;
        node.mn2 = min(left.mn2, right.mn2);
        node.mnc = left.mnc + right.mnc;
    } else if (left.mn1 < right.mn1) {
        node.mn1 = left.mn1;
        node.mn2 = min(left.mn2, right.mn1);
        node.mnc = left.mnc;
    } else {
        node.mn1 = right.mn1;
        node.mn2 = min(left.mn1, right.mn2);
        node.mnc = right.mnc;
    }
    return node;
}


void apply_min(int node, int l, int r, long long val) {
    if (segtree[node].mn1 >= val) {
        return;
    }
    segtree[node].sum -= (long long)(segtree[node].mn1 - val) * segtree[node].mnc;
    segtree[node].mn1 = val;
    return;
}

void compose(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    apply_min(2 * node + 1, l, mid, segtree[node].mn1);
    apply_min(2 * node + 2, mid + 1, r, segtree[node].mn1);
    return;
}

ll query_sum(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return segtree[node].sum;
    }
    compose(node, l, r);
    int mid = (l + r) / 2;
    return query_sum(l, mid, lq, rq, 2 * node + 1) + query_sum(mid + 1, r, lq, rq, 2 * node + 2);
}

void update_max(int l, int r, int lq, int rq, long long val, int node) {
    if (r < lq || l > rq || segtree[node].mn1 >= val) {
        return;
    }
    if (l >= lq && r <= rq && segtree[node].mn2 > val) {
        apply_min(node, l, r, val);
        return;
    }
    int mid = (l + r) / 2;
    compose(node, l, r);
    update_max(l, mid, lq, rq, val, 2 * node + 1);
    update_max(mid + 1, r, lq, rq, val, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
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
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int d : divs[a[i]]) {
            pos[d].push_back(i);
        }
    }
    for (int i = 1; i < N; i++) {
        if (pos[i].size() <= 1) {
            continue;
        }
        int l = pos[i][pos[i].size() - 2];
        if (l != 0) {
            upd[0].push_back({l - 1, i});
        }
        int r = pos[i][1];
        if (r != n - 1){
            upd[r + 1].push_back({n - 1, i});
        }
        l = pos[i][0], r = pos[i].back();
        if (l + 1 != r) {
            upd[l + 1].push_back({r - 1, i});
        }
    }
    build(0, n - 1, 0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto [r, j] : upd[i]) {
            update_max(0, n - 1, i, r, j, 0);
        }
        ans += query_sum(0, n - 1, i, n - 1, 0);
    }
    cout << ans;


    return 0;
}
