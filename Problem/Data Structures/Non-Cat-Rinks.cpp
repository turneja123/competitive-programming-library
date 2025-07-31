//https://basecamp.eolymp.com/en/problems/11864
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 20;
const int MAX = 1e7;

int a[N];
int h[N];

struct Node {
    int ct;
    ll cta;
    ll suma;
    int left;
    int right;
    Node() : ct(0), cta(0), suma(0), left(-1), right(-1) {}
};

int idx = 0;
Node nodes[MAX];
int root[N];

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
    return;
}

void update(int node_prev, int node, int l, int r, int ind, int a) {
    if (l == r) {
        nodes[node].ct = nodes[node_prev].ct + 1;
        nodes[node].cta = nodes[node_prev].cta + a;
        nodes[node].suma = nodes[node_prev].suma + (ll)a * ind;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[node].right = nodes[node_prev].right;
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, a);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[node].left = nodes[node_prev].left;
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, a);
    }
    nodes[node].ct = nodes[nodes[node].left].ct + nodes[nodes[node].right].ct;
    nodes[node].cta = nodes[nodes[node].left].cta + nodes[nodes[node].right].cta;
    nodes[node].suma = nodes[nodes[node].left].suma + nodes[nodes[node].right].suma;
    return;
}

int ct = 0; ll cta = 0, suma = 0;

void query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return;
    }
    if (lq <= l && rq >= r) {
        ct += nodes[node_r].ct - nodes[node_l].ct;
        cta += nodes[node_r].cta - nodes[node_l].cta;
        suma += nodes[node_r].suma - nodes[node_l].suma;
        return;
    }
    int mid = (l + r) / 2;
    query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq);
    query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int table[K][N];

void build_sparse(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = h[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query_sparse(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build_sparse(n);
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, N - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        update(root[i], root[i + 1], 0, N - 1, h[i], a[i]);
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int L = 2, R = n, d = 2;
        tuple<int, ll, ll> keep;
        while (L <= R) {
            int mid = (L + R) / 2;
            int need = (mid + 1) / 2 + 1;
            int x = query_sparse(l, r);
            if (x < need) {
                R = mid - 1;
                continue;
            }
            ct = 0;
            cta = 0;
            suma = 0;
            query(root[l], root[r + 1], 0, N - 1, mid, N - 1);
            if (ct >= mid + 1) {
                keep = {ct, cta, suma};
                d = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        auto [ct, cta, suma] = keep;
        ll ans = suma - cta * d;
        cout << ans << endl;
    }

    return 0;
}
