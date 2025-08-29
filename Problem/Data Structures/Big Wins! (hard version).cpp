//https://codeforces.com/contest/2126/problem/G2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

int ans = 0;

struct Node {
    int sum;
    int lazy;
    Node() {
        sum = 0, lazy = 0;
    }
    Node(int x) : sum(x), lazy(0) {}
};

int a[N];
int p[N];
int pref_mn[N];
Node segtree[4 * N];
vector<int> pos[N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = max(left.sum, right.sum);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].sum += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return -INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return max(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(p[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void calc(int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) / 2;
    vector<int> vals;
    for (int i = l; i <= r; i++) {
        vals.push_back(a[i]);
        pos[a[i]].push_back(i);
    }
    sort(vals.begin(), vals.end());
    for (int i = mid + 1; i <= r; i++) {
        p[i] = i - mid;
        pref_mn[i] = a[i];
        if (i != mid + 1) {
            pref_mn[i] = min(pref_mn[i], pref_mn[i - 1]);
        }
    }
    for (int i = mid; i >= l; i--) {
        p[i] = mid - i + 1;
        pref_mn[i] = a[i];
        if (i != mid) {
            pref_mn[i] = min(pref_mn[i], pref_mn[i + 1]);
        }
    }
    build(l, r, 0);
    int rt = r;
    for (int i = 0; i < vals.size(); i++) {
        int x = vals[i];
        if (i != 0 && x == vals[i - 1]) {
            continue;
        }
        int best = getSum(l, r, l, mid, 0);
        while (rt >= mid + 1 && best + getSum(l, r, rt, rt, 0) < 0) {
            rt--;
        }
        if (rt < mid + 1) {
            break;
        }
        ans = max(ans, x - pref_mn[rt]);
        for (int j : pos[x]) {
            if (j <= mid) {
                incUpdate(0, l, r, l, j, -2);
            } else {
                incUpdate(0, l, r, j, r, -2);
            }
        }
    }
    build(l, r, 0);
    int lf = l;
    for (int i = 0; i < vals.size(); i++) {
        int x = vals[i];
        if (i != 0 && x == vals[i - 1]) {
            continue;
        }
        int best = getSum(l, r, mid + 1, r, 0);
        while (lf <= mid && best + getSum(l, r, lf, lf, 0) < 0) {
            lf++;
        }
        if (lf > mid) {
            break;
        }
        ans = max(ans, x - pref_mn[lf]);
        for (int j : pos[x]) {
            if (j <= mid) {
                incUpdate(0, l, r, l, j, -2);
            } else {
                incUpdate(0, l, r, j, r, -2);
            }
        }
    }

    for (int x : vals) {
        pos[x].clear();
    }
    calc(l, mid);
    calc(mid + 1, r);
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
        }
        ans = 0;
        calc(0, n - 1);
        cout << ans << endl;
    }

    return 0;
}
