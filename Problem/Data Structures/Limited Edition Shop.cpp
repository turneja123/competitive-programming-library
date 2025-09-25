//https://codeforces.com/contest/2150/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

//dp[x] - najbolja vrednost tako da je bob uzeo prvih x objekta

struct Node {
    long long sum;
    long long lazy;
    Node() {
        lazy = 0;
    }
    Node(long long x) : sum(x), lazy(0) {}
};

Node segtree[4 * N];

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

void setUpdate(int node, int l, int r, int ind, ll val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(node * 2 + 1, l, mid, ind, val);
    } else {
        setUpdate(node * 2 + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

long long getSum(int l, int r, int lq, int rq, int node) {
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
        segtree[node] = Node(-INF);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

tuple<int, int, int> a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> get<2>(a[i]);
        }
        for (int i = 0; i < n; i++) {
            int j;
            cin >> j;
            j--;
            get<0>(a[j]) = i + 1;
        }
        for (int i = 0; i < n; i++) {
            int j;
            cin >> j;
            j--;
            get<1>(a[j]) = i + 1;
        }
        sort(a, a + n);
        build(0, n, 0);
        setUpdate(0, 0, n, 0, 0);
        for (int i = 0; i < n; i++) {
            auto [x, y, v] = a[i];
            ll z = getSum(0, n, 0, y - 1, 0);
            setUpdate(0, 0, n, y, z);
            incUpdate(0, 0, n, 0, y - 1, v);
        }
        cout << getSum(0, n, 0, n, 0) << endl;
    }


    return 0;
}
