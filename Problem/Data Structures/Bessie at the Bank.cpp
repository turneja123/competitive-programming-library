//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-rR34b-aSpMnefp23TAWu3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
ll a[N];


vector<ll> vals;

void build(int node, int l, int r) {
    if (l == r) {
        for (int i = 0; i < vals.size(); i++) {
            if (a[l] % vals[i] == 0) {
                nodes[node].val |= 1 << i;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    nodes[node].val = nodes[nodes[node].left].val & nodes[nodes[node].right].val;
    return;
}

void update(int node_prev, int node, int l, int r, int ind, ll cur) {
    if (l == r) {
        nodes[node].val = 0;
        for (int i = 0; i < vals.size(); i++) {
            if (cur % vals[i] == 0) {
                nodes[node].val |= 1 << i;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, cur);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, cur);
    }
    nodes[node].val = nodes[nodes[node].left].val & nodes[nodes[node].right].val;
    return;
}

int main() {
    IOS;
    int n, q, d;
    cin >> n >> q >> d;
    vals.resize(d);
    for (int i = 0; i < d; i++) {
        cin >> vals[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, n - 1);
    ll ans = 0;
    for (int j = 0; j < d; j++) {
        int c = (1 << j) & nodes[0].val;
        if (c) {
            ans += vals[j];
        }
    }
    cout << ans << endl;
    for (int i = 0; i < q; i++) {
        int t, j; ll x;
        cin >> t >> j >> x;
        j--;
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[t], root[i + 1], 0, n - 1, j, x);
        ll ans = 0;
        for (int j = 0; j < d; j++) {
            int c = (1 << j) & nodes[root[i + 1]].val;
            if (c) {
                ans += vals[j];
            }
        }
        cout << ans << endl;
    }

    return 0;
}
