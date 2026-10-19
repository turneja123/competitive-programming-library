//bbc15
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 5e6;
const int MOV = 2e6;

struct Node {
    int l;
    int r;
    int mn;
    int ct_mn;
    int lazy;

    Node() {
        l = -1;
        r = -1;
        mn = MAX;
        ct_mn = 0;
        lazy = 0;
    }

    Node(int _l, int _r) {
        l = -1;
        r = -1;
        mn = 0;
        ct_mn = _r - _l + 1;
        lazy = 0;
    }

};

Node nodes[MAX];
int idx = 0;


void apply(int l, int r, int node) {
    nodes[node].mn += nodes[node].lazy;
    if (l != r) {
        int mid = (l + r) / 2;
        if (nodes[node].l == -1) {
            nodes[node].l = idx;
            nodes[idx++] = Node(l, mid);
        }
        if (nodes[node].r == -1) {
            nodes[node].r = idx;
            nodes[idx++] = Node(mid + 1, r);
        }
        nodes[nodes[node].l].lazy += nodes[node].lazy;
        nodes[nodes[node].r].lazy += nodes[node].lazy;
    }


    nodes[node].lazy = 0;
}

void incUpdate(int l, int r, int node, int lq, int rq, int add) {
    if (lq > r || rq < l) {
        return;
    }
    apply(l, r, node);
    if (l >= lq && r <= rq) {
        nodes[node].lazy += add;
        return;
    }
    int mid = (l + r) / 2;
    incUpdate(l, mid, nodes[node].l, lq, rq, add);
    incUpdate(mid + 1, r, nodes[node].r, lq, rq, add);
    apply(l, mid, nodes[node].l);
    apply(mid + 1, r, nodes[node].r);
    nodes[node].mn = min(nodes[nodes[node].l].mn, nodes[nodes[node].r].mn);
    nodes[node].ct_mn = 0;
    if (nodes[nodes[node].l].mn == nodes[node].mn) {
        nodes[node].ct_mn += nodes[nodes[node].l].ct_mn;
    }
    if (nodes[nodes[node].r].mn == nodes[node].mn) {
        nodes[node].ct_mn += nodes[nodes[node].r].ct_mn;
    }
}


int main() {
    IOS;
    cout << fixed;
    cout << setprecision(1);
    nodes[idx++] = Node(0, MAX);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += MOV;
    }
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        int g;
        cin >> g;
        mp[a[i]] = g;
        incUpdate(0, MAX, 0, a[i] - g, a[i] + g - 1, 1);
    }
    int sz = MAX + 1;
    apply(0, MAX, 0);
    int zeros = 0;
    if (nodes[0].mn == 0) {
        zeros += nodes[0].ct_mn;
    }
    int ans = sz - zeros;
    cout << (double)ans / (double)2.0 << endl;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int pos, val;
            cin >> pos >> val;
            pos += MOV;
            auto it = mp.find(pos);
            if (it != mp.end()) {
                val += it->second;
                incUpdate(0, MAX, 0, pos - it->second, pos + it->second - 1, -1);
            }
            mp[pos] = val;
            incUpdate(0, MAX, 0, pos - val, pos + val - 1, 1);
        } else {
            int pos;
            cin >> pos;
            pos += MOV;
            auto it = mp.find(pos);

            incUpdate(0, MAX, 0, pos - it->second, pos + it->second - 1, -1);
            mp.erase(it);
        }
        apply(0, MAX, 0);
        int zeros = 0;
        if (nodes[0].mn == 0) {
            zeros += nodes[0].ct_mn;
        }
        int ans = sz - zeros;
        cout << (double)ans / (double)2.0 << endl;
    }

    return 0;
}
