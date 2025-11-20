//https://atcoder.jp/contests/abc418/tasks/abc418_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;


int a[N];
ll dp[N][2][2];
long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    if (k > n || n < 0 || k < 0) {
        return 0;
    }
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

set<int> st;

struct Node {
    ll dp[2][2];
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(ll a00, ll a01, ll a10, ll a11) {
        sentinel = 0;
        dp[0][0] = a00;
        dp[0][1] = a01;
        dp[1][0] = a10;
        dp[1][1] = a11;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    if (left.sentinel && right.sentinel) {
        return node;
    }
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    node.sentinel = 0;
    node.dp[0][0] = (left.dp[0][0] * right.dp[0][0] + left.dp[0][1] * right.dp[0][0] + left.dp[0][0] * right.dp[1][0]) % M;
    node.dp[0][1] = (left.dp[0][0] * right.dp[0][1] + left.dp[0][1] * right.dp[0][1] + left.dp[0][0] * right.dp[1][1]) % M;
    node.dp[1][0] = (left.dp[1][0] * right.dp[0][0] + left.dp[1][1] * right.dp[0][0] + left.dp[1][0] * right.dp[1][0]) % M;
    node.dp[1][1] = (left.dp[1][0] * right.dp[0][1] + left.dp[1][1] * right.dp[0][1] + left.dp[1][0] * right.dp[1][1]) % M;
    return node;
}

void update(int l, int r, int ind, int n, int k, int node) {
    if (l == r) {
        if (n == -1) {
            segtree[node] = Node();
            return;
        }
        if (k < 0 || k > n) {
            segtree[node] = Node(0, 0, 0, 0);
            return;
        }
        if (n == 1) {
            if (k == 0) {
                segtree[node] = Node(1, 0, 0, 0);
            } else {
                segtree[node] = Node(0, 0, 0, 1);
            }
            return;
        }
        segtree[node] = Node(binomial(n - k - 1, k), binomial(n - k - 1, k - 1), binomial(n - k - 1, k - 1), binomial(n - k - 1, k - 2));
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, n, k, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, n, k, 2 * node + 2);
    }
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        if (l == 0) {
            segtree[node] = Node(1, 0, 0, 0);
        } else {
            segtree[node] = Node();
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int n, q;
    cin >> n >> q;
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = -1;
    }
    dp[1][1][1] = 1;
    dp[1][0][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 1; j++) {
            dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % M;
            dp[i][j][1] = dp[i - 1][j][0];
        }
    }
    st.insert(0);
    build(0, n, 0);
    while (q--) {
        int x, y;
        cin >> x >> y;
        a[x] = y;
        st.insert(x);
        auto it = st.find(x);
        if (a[x] != -1) {
            it--;
            update(0, n, x, x - *it, a[x] - a[*it], 0);
            it++;
            it++;
            if (it != st.end()) {
                update(0, n, *it, *it - x, a[*it] - a[x], 0);
            }
        } else {
            update(0, n, x, -1, -1, 0);
            it--;
            int l = *it;
            it++;
            it++;
            if (it != st.end()) {
                update(0, n, *it, *it - l, a[*it] - a[l], 0);
            }
            st.erase(st.find(x));
        }


        int r = *st.rbegin();
        ll ans = 0;
        if (r == n) {
            ans = (segtree[0].dp[0][0] + segtree[0].dp[0][1] + segtree[0].dp[1][0] + segtree[0].dp[1][1]) %M;
            cout << ans << endl;
        } else {
            ans = (ans + segtree[0].dp[0][0] * dp[n - r][0][0] + segtree[0].dp[0][1] * dp[n - r][0][0] + segtree[0].dp[0][0] * dp[n - r][1][0]) % M;
            ans = (ans + segtree[0].dp[0][0] * dp[n - r][0][1] + segtree[0].dp[0][1] * dp[n - r][0][1] + segtree[0].dp[0][0] * dp[n - r][1][1]) % M;
            ans = (ans + segtree[0].dp[1][0] * dp[n - r][0][0] + segtree[0].dp[1][1] * dp[n - r][0][0] + segtree[0].dp[1][0] * dp[n - r][1][0]) % M;
            ans = (ans + segtree[0].dp[1][0] * dp[n - r][0][1] + segtree[0].dp[1][1] * dp[n - r][0][1] + segtree[0].dp[1][0] * dp[n - r][1][1]) % M;
            cout << ans << endl;
        }

    }
    return 0;
}
