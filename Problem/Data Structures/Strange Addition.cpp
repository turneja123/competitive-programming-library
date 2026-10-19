//https://codeforces.com/contest/1380/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 998244353;

struct Node {
    ll dp[2][2];
    int l;
    int r;
    int sentinel;
    Node() {
        sentinel = 1;
    }
    Node(int x, int i) {
        sentinel = 0;
        l = i;
        r = i;
        dp[1][1] = 0;
        dp[0][1] = 0;
        dp[1][0] = 0;
        dp[0][0] = x + 1;
    }
};

Node segtree[4 * N];
int a[N];
ll inv[N];

Node combine(Node left, Node right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node = Node();
    node.sentinel = 0;
    node.l = left.l;
    node.r = right.r;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            node.dp[i][j] = 0;
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                node.dp[i][k] = (node.dp[i][k] + left.dp[i][j] * (right.dp[0][k] + right.dp[1][k])) % M;
            }
        }
    }
    int z = 10 * a[left.r] + a[right.l];
    if (z <= 18 && z >= 10) {
        int l = z - 9;
        ll ways = 9 - l + 1;
        for (int i = 0; i < 2; i++) {
            for (int k = 0; k < 2; k++) {
                ll L = left.dp[i][0] * inv[a[left.r] + 1] % M;
                ll R = right.dp[0][k] * inv[a[right.l] + 1] % M;
                int lf = (left.l == left.r ? 1 : i);
                int rt = (right.l == right.r ? 1 : k);
                node.dp[lf][rt] = (node.dp[lf][rt] + L * R % M * ways) % M;
            }
        }
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

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = Node(a[l], l);
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
        segtree[node] = Node(a[l], l);
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    set<int> st;
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
        if (a[i] != 0) {
            st.insert(i);
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int j, d;
        cin >> j >> d;
        j--;
        if (a[j] != 0) {
            st.erase(j);
        }
        a[j] = d;
        update(0, n - 1, j, 0);
        if (a[j] != 0) {
            st.insert(j);
        }
        if (st.empty()) {
            cout << 1 << endl;
            continue;
        }
        int l = *st.begin();
        Node node = query(0, n - 1, l, n - 1, 0);
        ll ans = 0;
        for (int i : {0, 1}) {
            for (int j : {0, 1}) {
                ans = (ans + node.dp[i][j]) % M;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
