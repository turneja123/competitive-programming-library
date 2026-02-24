//https://codeforces.com/contest/2201/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    int pref;
    int suf;
    int mx;
    int uniform;
    ll sum;

    Node() {
        pref = 0;
        suf = 0;
        mx = -1;
        uniform = 0;
        sum = 0;
    }

    Node(int x) {
        pref = 1;
        suf = 1;
        mx = x;
        uniform = 1;
        sum = 1;
    }
};

Node segtree[4 * N];
int a[N];
int b[N];
set<int> pos[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.uniform = left.uniform && right.uniform && left.mx == right.mx;

    if (left.mx > right.mx) {
        node.mx = left.mx;
        node.pref = left.pref;
        node.suf = 0;
        node.sum = left.sum;
    } else if (left.mx < right.mx) {
        node.mx = right.mx;
        node.suf = right.suf;
        node.pref = 0;
        node.sum = right.sum;
    } else {
        node.mx = left.mx;
        node.pref = left.pref + (left.uniform ? right.pref : 0);
        node.suf = right.suf + (right.uniform ? left.suf : 0);
        node.sum = left.sum + right.sum + (ll)left.suf * right.pref;
    }

    return node;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] = Node();
        if (val != -1) {
            segtree[node] = Node(val);
        }
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
        segtree[node] = Node();
        if (a[l] != -1) {
            segtree[node] = Node(a[l]);
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            pos[b[i]].insert(i);
        }
        for (int i = 0; i < n; i++) {
            if (*pos[b[i]].begin() == i) {
                a[i] = *pos[b[i]].rbegin() - i;
            } else {
                a[i] = -1;
            }
        }
        build(0, n - 1, 0);
        for (int i = 0; i < q; i++) {
            int j, x;
            cin >> j >> x;
            j--;
            int y = b[j];

            update(0, n - 1, *pos[y].begin(), -1, 0);
            pos[y].erase(j);
            if (pos[y].size()) {
                update(0, n - 1, *pos[y].begin(), *pos[y].rbegin() - *pos[y].begin(), 0);
            }

            if (pos[x].size()) {
                update(0, n - 1, *pos[x].begin(), -1, 0);
            }
            pos[x].insert(j);
            update(0, n - 1, *pos[x].begin(), *pos[x].rbegin() - *pos[x].begin(), 0);
            b[j] = x;
            cout << segtree[0].mx << " " << (segtree[0].mx == 0 ? 0 : segtree[0].sum) << endl;
        }
        for (int i = 1; i <= n; i++) {
            pos[i].clear();
        }

    }

    return 0;
}
