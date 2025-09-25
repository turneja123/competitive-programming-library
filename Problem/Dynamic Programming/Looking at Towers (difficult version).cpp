//https://codeforces.com/contest/2144/problem/E2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll M = 998244353;

int a[N];

ll dp[N];
ll dp_lf[N], dp_rt[N];

struct Node {
    long long sum;
    long long lazy;
    Node() {
        lazy = 1;
    }
    Node(long long x) : sum(x), lazy(1) {}
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = (left.sum + right.sum) % M;
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy = segtree[child].lazy * segtree[parent].lazy % M;

}

void apply(int node, int l, int r) {
    segtree[node].sum = segtree[node].lazy * segtree[node].sum % M;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 1;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = segtree[node].lazy * 2 % M;
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

void upd(int l, int r, int ind, ll val, int node) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(l, mid, ind, val, 2 * node + 1);
    } else {
        upd(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

long long getSum(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return getSum(l, mid, ind, 2 * node + 1);
    } else {
        return getSum(mid + 1, r, ind, 2 * node + 2);
    }
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
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> vals;
        map<int, int> id;
        for (int i = 0; i < n; i++) {
            if (a[i] > mx) {
                mx = a[i];
                vals.push_back(a[i]);
                id[a[i]] = vals.size();
            }
        }
        int m = vals.size();
        build(0, m - 1, 0);
        for (int i = 0; i < n; i++) {
            if (id[a[i]] != 0) {
                int j = id[a[i]] - 1;
                ll add = 0;
                if (a[i] != vals.back()) {
                    add = (add + getSum(0, m - 1, j, 0)) % M;
                }
                add = (add + (j == 0 ? 1 : getSum(0, m - 1, j - 1, 0))) % M;
                if (a[i] == vals.back()) {
                    dp_lf[i] = add;
                }
                dp[j] = (getSum(0, m - 1, j, 0) + add) % M;
                upd(0, m - 1, j, dp[j], 0);
            }
            int r = upper_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
            if (r != vals.size()) {
                incUpdate(0, 0, m - 1, r, m - 1, 2);
            }
        }
        vals.clear();
        id.clear();
        for (int i = 0; i < n; i++) {
            dp[i] = 0;
        }
        ////////////////////
        mx = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > mx) {
                mx = a[i];
                vals.push_back(a[i]);
                id[a[i]] = vals.size();
            }
        }
        m = vals.size();
        build(0, m - 1, 0);
        for (int i = n - 1; i >= 0; i--) {
            if (id[a[i]] != 0) {
                int j = id[a[i]] - 1;
                ll add = 0;
                add = (add + getSum(0, m - 1, j, 0)) % M;
                add = (add + (j == 0 ? 1 : getSum(0, m - 1, j - 1, 0))) % M;
                if (a[i] == vals.back()) {
                    dp_rt[i] = add;
                }
                dp[j] = (getSum(0, m - 1, j, 0) + add) % M;
                upd(0, m - 1, j, dp[j], 0);
            }
            int r = upper_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
            if (r != vals.size()) {
                incUpdate(0, 0, m - 1, r, m - 1, 2);
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp_lf[i] * dp_rt[i]) % M;
        }
        cout << ans << endl;

        for (int i = 0; i < n; i++) {
            dp[i] = 0;
            dp_lf[i] = 0, dp_rt[i] = 0;
        }
    }
    return 0;
}
