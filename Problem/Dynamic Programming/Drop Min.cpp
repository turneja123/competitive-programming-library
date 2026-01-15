//https://atcoder.jp/contests/arc212/tasks/arc212_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const ll M = 998244353;

int table_mx[K][N];
int mx[K][N];
int a[N];



void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mx[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mx[k - 1][i] >= table_mx[k - 1][i + (1 << (k - 1))]) {
                table_mx[k][i] = table_mx[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table_mx[k][i] = table_mx[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mx[k][l] >= table_mx[k][r - (1 << k) + 1]) {
        b = mx[k][l];
    } else {
        b = mx[k][r - (1 << k) + 1];
    }
    return b;
}

ll inv[N];
ll fact[N];
ll factinv[N];

ll binomial(ll n, ll k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

struct Node {
    int left;
    int right;
    int l;
    int r;
    int sz;

    ll dp;
    Node() {
        left = -1;
        right = -1;
        l = 0;
        r = 0;
        dp = 0;
        sz = 0;
    }
};

int idx = 0;
Node nodes[N];

int get_sz(int node) {
    if (node == -1) {
        return 0;
    }
    return nodes[node].sz;
}

int cartesian(int l, int r, int par, int s) {
    if (l > r) {
        return -1;
    }
    int node = idx;
    nodes[idx++] = Node();
    if (s == 0) {
        nodes[node].l = nodes[par].l;
        nodes[node].r = 1;
    } else if (s == 1) {
        nodes[node].l = 1;
        nodes[node].r = nodes[par].r;
    }

    int mid = query(l, r);
    nodes[node].left = cartesian(l, mid - 1, node, 0);
    nodes[node].right = cartesian(mid + 1, r, node, 1);
    nodes[node].sz = 1 + get_sz(nodes[node].left) + get_sz(nodes[node].right);
    return node;
}

void dfs(int node) {
    if (nodes[node].left != -1) {
        dfs(nodes[node].left);
    }
    if (nodes[node].right != -1) {
        dfs(nodes[node].right);
    }
    int l = get_sz(nodes[node].left), r = get_sz(nodes[node].right);
    if (node == 0) {
        nodes[node].dp = binomial(l + r, l);
    } else {
        nodes[node].dp = ((nodes[node].l ? binomial(l + r + 1, r) : 0) + (nodes[node].r ? binomial(l + r + 1, l) : 0) + (nodes[node].l && nodes[node].r ? M - binomial(l + r, r) : 0)) % M;
    }
    if (nodes[node].left != -1) {
        nodes[node].dp = nodes[node].dp * nodes[nodes[node].left].dp % M;
    }
    if (nodes[node].right != -1) {
        nodes[node].dp = nodes[node].dp * nodes[nodes[node].right].dp % M;
    }
}

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    cartesian(0, n - 1, -1, -1);
    dfs(0);
    cout << nodes[0].dp;


    return 0;
}
