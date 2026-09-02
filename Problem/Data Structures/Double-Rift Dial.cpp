//https://codeforces.com/contest/2249/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
int pos[N];

struct Node {
    int pref;
    int sum;
    int val;
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(int x) {
        pref = x;
        sum = x;
        val = x;
        sentinel = 0;
    }
};

Node segtree[4 * N];

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
    node.val = max({left.val, right.val, node.pref});
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
        segtree[node] = Node(0);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void calc(int x, int n) {
    int cost = 1;
    if (x != 0 && pos[x] > pos[x - 1]) {
        cost--;
    }
    if (x != n - 1 && pos[x] > pos[x + 1]) {
        cost--;
    }
    update(0, 2 * n - 1, pos[x], cost, 0);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            a[i + n] = a[i];
            pos[a[i]] = i;
        }
        build(0, 2 * n - 1, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            calc(a[i], n);
        }
        Node node = query(0, 2 * n - 1, 0, n - 1, 0);
        if (node.val <= 2) {
            ans++;
        }
        for (int i = n; i < 2 * n - 1; i++) {
            pos[a[i]] = i;
            calc(a[i], n);
            if (a[i] != 0) {
                calc(a[i] - 1, n);
            }
            if (a[i] != n - 1) {
                calc(a[i] + 1, n);
            }
            Node node = query(0, 2 * n - 1, i - (n - 1), i, 0);
            if (node.val <= 2) {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
