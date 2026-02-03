//https://www.spoj.com/problems/GSS3/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    ll pref;
    ll suf;
    ll sum;
    ll val;
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(ll x) {
        pref = x, suf = x, sum = x, val = x;
        sentinel = 0;
    }
};

Node combine(Node &left, Node &right) {
    Node node = Node();
    node.sentinel = 0;
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    node.suf = max(right.suf, right.sum + left.suf);
    node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
    return node;
}

ll a[N];
Node seg[2 * N];


void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = Node(a[i]);
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = combine(seg[2 * i], seg[2 * i + 1]);
    }
}

void update(int pos, ll val, int n) {
    pos += n;
    seg[pos] = Node(val);
    while (pos > 1) {
        pos /= 2;
        seg[pos] = combine(seg[2 * pos], seg[2 * pos + 1]);
    }
}

ll query(int l, int r, int n) {
    r++;
    l += n;
    r += n;
    Node L, R;
    while (l < r) {
        if (r % 2 == 1) {
            R = combine(seg[--r], R);
        }
        if (l % 2 == 1) {
            L = combine(L, seg[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return combine(L, R).val;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int j, val;
            cin >> j >> val;
            j--;
            update(j, val, n);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << query(l, r, n) << endl;
        }

    }
    return 0;
}
