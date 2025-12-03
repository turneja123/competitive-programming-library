//https://codeforces.com/contest/1287/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 998244353;

int x[N];
int v[N];
int p[N];
int can_o[N];
int can_r[N];
int can_l[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

struct Node {
    int l;
    int r;
    ll dp[2][2];

    Node() {}
    Node(int i) {
        l = i;
        r = i;
        dp[0][1] = 0;
        dp[1][0] = 0;
        dp[1][1] = p[i] * modPow(100, M - 2) % M;
        dp[0][0] = (100 - p[i]) * modPow(100, M - 2) % M;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.l = left.l;
    node.r = right.r;

    node.dp[0][0] = ((can_l[left.r] ? left.dp[0][0] * right.dp[0][0] : 0) + (can_o[left.r] ? left.dp[0][1] * right.dp[0][0] : 0) + left.dp[0][0] * right.dp[1][0] + (can_r[left.r] ? left.dp[0][1] * right.dp[1][0] : 0)) % M;
    node.dp[0][1] = ((can_l[left.r] ? left.dp[0][0] * right.dp[0][1] : 0) + (can_o[left.r] ? left.dp[0][1] * right.dp[0][1] : 0) + left.dp[0][0] * right.dp[1][1] + (can_r[left.r] ? left.dp[0][1] * right.dp[1][1] : 0)) % M;
    node.dp[1][0] = ((can_l[left.r] ? left.dp[1][0] * right.dp[0][0] : 0) + (can_o[left.r] ? left.dp[1][1] * right.dp[0][0] : 0) + left.dp[1][0] * right.dp[1][0] + (can_r[left.r] ? left.dp[1][1] * right.dp[1][0] : 0)) % M;
    node.dp[1][1] = ((can_l[left.r] ? left.dp[1][0] * right.dp[0][1] : 0) + (can_o[left.r] ? left.dp[1][1] * right.dp[0][1] : 0) + left.dp[1][0] * right.dp[1][1] + (can_r[left.r] ? left.dp[1][1] * right.dp[1][1] : 0)) % M;
    return node;
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = Node(l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


bool comp(tuple<int, int, int, int> x, tuple<int, int, int, int> y) {
    auto [a, b, _x, _] = x;
    auto [c, d, _y, __] = y;
    return (ll)a * d - (ll)c * b > 0;
}

bool eq(tuple<int, int, int, int> x, tuple<int, int, int, int> y) {
    auto [a, b, _x, _] = x;
    auto [c, d, _y, __] = y;
    return (ll)a * d == (ll)c * b;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a;
    vector<tuple<int, int, int, int>> adj;
    for (int i = 0; i < n; i++) {
        int x, v, p;
        cin >> x >> v >> p;
        a.push_back(make_tuple(x, v, p));
    }
    if (n == 1) {
        cout << 0;
        return 0;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        x[i] = get<0>(a[i]);
        v[i] = get<1>(a[i]);
        p[i] = get<2>(a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        auto [x1, v1, _1] = a[i];
        auto [x2, v2, _2] = a[i + 1];
        adj.push_back(make_tuple(x2 - x1, v1 + v2, i, 0));
        if (v1 > v2) {
            adj.push_back(make_tuple(x2 - x1, v1 - v2, i, 1));
            can_l[i] = 1;
        } else if (v1 < v2) {
            adj.push_back(make_tuple(x2 - x1, v2 - v1, i, 2));
            can_r[i] = 1;
        } else {
            can_r[i] = 1;
            can_l[i] = 1;
        }
    }
    sort(adj.begin(), adj.end(), comp);
    ll ans = 0;
    build(0, n - 1, 0);
    ll last = (segtree[0].dp[0][0] + segtree[0].dp[0][1] + segtree[0].dp[1][0] + segtree[0].dp[1][1]) % M;
    int m = adj.size();
    for (int i = 0; i < m;) {
        auto diff = adj[i];
        vector<pair<int, int>> upd;
        while (i < m && eq(diff, adj[i])) {
            upd.push_back({get<2>(adj[i]), get<3>(adj[i])});
            i++;
        }
        for (auto [j, f] : upd) {
            if (f == 0) {
                can_o[j] = 1;
            } else if (f == 1) {
                can_r[j] = 1;
            } else {
                can_l[j] = 1;
            }
            update(0, n - 1, j, 0);
        }
        ll cur = (segtree[0].dp[0][0] + segtree[0].dp[0][1] + segtree[0].dp[1][0] + segtree[0].dp[1][1]) % M;
        ans = (ans + (cur - last + M) * get<0>(diff) % M * modPow(get<1>(diff), M - 2)) % M;
        last = cur;
    }
    cout << ans;


    return 0;
}
