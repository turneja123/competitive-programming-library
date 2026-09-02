//https://atcoder.jp/contests/arc228/tasks/arc228_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int p[N];
int lf[N];

int pos[N];
int ct[N];

struct Node {
    int sentinel;
    int who;
    ll val;
    Node() {
        sentinel = 1;
    }
    Node(int i, ll x) {
        sentinel = 0;
        who = i;
        val = x;
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
    if (left.val < right.val) {
        node.val = left.val;
        node.who = left.who;
    } else {
        node.val = right.val;
        node.who = right.who;
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

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = Node(l, val);
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

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        a[pos[i]] = v;
    }
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (st.size() && p[st.top()] < p[i]) {
            st.pop();
        }
        if (st.empty()) {
            lf[i] = 0;
        } else {
            lf[i] = st.top();
        }
        st.push(i);
    }
    for (int i = 0; i < n; i++) {
        update(0, n - 1, i, (ll)(ct[i] + 1) * (ct[i] + 1) * a[i], 0);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x = i;
        if (x == 0) {
            continue;
        }
        Node node = query(0, n - 1, lf[x], x - 1, 0);
        int j = node.who;
        ans += node.val;
        ll cur = (ll)(ct[j] + 1) * (ct[j] + 1) * a[j];
        ct[j]++;
        update(0, n - 1, j, (ll)(ct[j] + 1) * (ct[j] + 1) * a[j] - cur, 0);
    }
    cout << ans;

    return 0;
}
