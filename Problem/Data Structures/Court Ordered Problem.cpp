//https://olympicode.rs/problem/38
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 21;

struct Node {
    int popcnt[K];
    int pref[K];
    int suf[K];
    int mx[K];

    Node() {
        for (int i = 0; i < K; i++) {
            mx[i] = -1;
            popcnt[i] = 0;
            pref[i] = 0;
            suf[i] = (1 << K) - 1;
        }
    }
    Node(int x) {
        for (int i = 0; i < K; i++) {
            mx[i] = -1;
            popcnt[i] = 0;
            pref[i] = 0;
            suf[i] = (1 << K) - 1;
        }
        int j = __builtin_popcount(x);
        mx[j] = x;
        popcnt[j]++;
        pref[j] |= x;
        suf[j] &= x;
        for (int i = 1; i < K; i++) {
            pref[i] = pref[i - 1] | pref[i];
        }
        for (int i = K - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] & suf[i];
        }
    }
};

Node segtree[4 * N];
int a[N];

Node combine(Node left, Node right) {
    Node node = Node();
    for (int i = 0; i < K; i++) {
        node.popcnt[i] = left.popcnt[i] + right.popcnt[i];
        node.mx[i] = max(left.mx[i], right.mx[i]);
        node.pref[i] = left.pref[i] | right.pref[i];
        node.suf[i] = left.suf[i] & right.suf[i];
    }
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
        segtree[node] = Node(a[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            update(0, n - 1, l, a[r], 0);
            update(0, n - 1, r, a[l], 0);
            swap(a[l], a[r]);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            Node node = query(0, n - 1, l, r, 0);
            int ans = 0;
            for (int i = 0; i < K; i++) {
                if (node.popcnt[i] != 1) {
                    continue;
                }
                int L = node.mx[i] | node.pref[i];
                int R = node.mx[i] & node.suf[i];
                if (L == node.mx[i] && R == node.mx[i]) {
                    ans++;
                }
            }
            cout << ans << endl;


        }
    }
    return 0;
}
