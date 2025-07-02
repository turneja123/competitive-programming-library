//https://codeforces.com/problemset/problem/1195/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 1e7;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int last[N];
vector<int> a;
int b[N];
int lf[N];
int rt[N];

int ans;

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + 1;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val - nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int main() {
    IOS;
    int n;
    cin >> n;
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        lf[i] = a.size();
        vector<pair<int, int>> pt;
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            pt.emplace_back(x, y);
        }
        for (int i = 0; i < k; i++) {
            int dx = pt[i].first - pt[(i - 1 + k) % k].first;
            int dy = pt[i].second - pt[(i - 1 + k) % k].second;
            int sgnx = (dx >= 0 ? 1 : -1), sgny = (dy >= 0 ? 1 : -1);
            if (dx != 0 && dy != 0) {
                dx = dx * sgnx;
                dy = dy * sgny;
                int g = __gcd(dx, dy);
                dx /= g;
                dy /= g;
                dx = dx * sgnx;
                dy = dy * sgny;
            } else if (dx == 0) {
                dy = sgny;
            } else {
                dx = sgnx;
            }
            auto it = mp.find({dx, dy});
            if (it == mp.end()) {
                mp[{dx, dy}] = mp.size();
            }
            a.push_back(mp[{dx, dy}]);
        }
        rt[i] = a.size();
    }
    int m = mp.size();
    n = a.size();
    for (int i = 0; i < m; i++) {
        last[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        b[i] = last[a[i]];
        last[a[i]] = i;
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, n - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, n - 1, b[i] + 1);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        l = lf[l] + 1;
        r = rt[r];
        cout << query(root[l - 1], root[r], 0, n - 1, 0, l - 1) << endl;
    }

    return 0;
}
