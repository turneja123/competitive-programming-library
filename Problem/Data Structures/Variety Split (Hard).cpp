//https://atcoder.jp/contests/abc397/tasks/abc397_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

struct Node {
    int pref;
    int suf;
    int sum;
    int val;
    Node() : pref(0), suf(0), sum(0), val(0) {}
    Node(int x) : pref(x), suf(x), sum(x), val(x) {}
};

Node segtree[4 * N];
int a[N];
vector<int> pos[N];
int ptr[N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.val == -INF) {
        return right;
    }
    if (right.val == -INF) {
        return left;
    }
    node.sum = left.sum + right.sum;
    node.pref = max(left.pref, left.sum + right.pref);
    node.suf = max(right.suf, right.sum + left.suf);
    node.val = max({left.val, right.val, node.pref, node.suf, left.suf + right.pref});
    return node;
}

Node query(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        Node sentinel(-INF);
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
        segtree[node].val += val;
        segtree[node].pref += val;
        segtree[node].suf += val;
        segtree[node].sum += val;
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
    int uniq = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        if (pos[a[i]].empty()) {
            uniq++;
        }
        pos[a[i]].push_back(i);
    }
    set<int> st;
    for (int i = 0; i < n; i++) {
        if (pos[i].size()) {
            update(0, n - 1, pos[i][0], 1, 0);
            update(0, n - 1, pos[i].back(), -1, 0);
        }
    }
    int ans = 0;
    for (int i = 0; i < n - 2; i++) {
        st.insert(a[i]);
        ptr[a[i]]++;
        if (ptr[a[i]] != pos[a[i]].size()) {
            update(0, n - 1, pos[a[i]][ptr[a[i]]], 1, 0);
        } else {
            uniq--;
        }
        Node node = query(0, n - 1, i + 1, n - 1, 0);
        int cur = st.size() + uniq + node.pref;
        ans = max(ans, cur);
    }
    cout << ans;
    return 0;
}
