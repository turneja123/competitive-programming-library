//https://codeforces.com/contest/1046/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Item {
    int x;
    int xl;
    int xr;
    int i;
    int il;
    int ir;
    int r;
};

const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val += val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = 0;
    if (nodes[node].left != -1) {
        nodes[node].val += nodes[nodes[node].left].val;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
    }
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    vector<int> compr_x;
    vector<int> compr_i;
    vector<Item> items;
    for (int i = 0; i < n; i++) {
        int x, r, q;
        cin >> x >> r >> q;
        Item item = {x, x - r, x + r, q, q - k, q + k, r};
        items.push_back(item);
        compr_x.push_back(x);
        compr_x.push_back(x - r);
        compr_x.push_back(x + r);
        compr_i.push_back(q);
        compr_i.push_back(q - k);
        compr_i.push_back(q + k);
    }
    sort(compr_x.begin(), compr_x.end());
    compr_x.erase(unique(compr_x.begin(), compr_x.end()), compr_x.end());
    sort(compr_i.begin(), compr_i.end());
    compr_i.erase(unique(compr_i.begin(), compr_i.end()), compr_i.end());

    sort(items.begin(), items.end(), [&](Item &a, Item &b) {return a.r > b.r;});
    ll ans = 0;
    idx = compr_i.size();

    auto id = [&](int x, vector<int> &v) -> int {
        return lower_bound(v.begin(), v.end(), x) - v.begin();
    };

    for (Item item : items) {
        auto [x, xl, xr, i, il, ir, _] = item;
        x = id(x, compr_x);
        xl = id(xl, compr_x);
        xr = id(xr, compr_x);
        i = id(i, compr_i);
        il = id(il, compr_i);
        ir = id(ir, compr_i);

        for (int j = il; j <= ir; j++) {
            ans += query(j, 0, compr_x.size() - 1, xl, xr);
        }
        update(i, 0, compr_x.size() - 1, x, 1);
    }
    cout << ans;

    return 0;
}
