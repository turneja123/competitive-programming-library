//https://www.codechef.com/problems/PRMQ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int MAX = 3e7 + 5;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int root[N];
int a[N];
int ans;
int spf[N];
bool is_prime[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

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

void update(int node_prev, int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = nodes[node_prev].val + val;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left != -1) {
            int ln = nodes[nodes[node].left].left, rn = nodes[nodes[node].left].right;
            nodes[node].left = idx;
            nodes[idx] = Node();
            nodes[idx].left = ln, nodes[idx].right = rn;
            idx++;
        } else {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }

        if (nodes[node].right == -1) {
            nodes[node].right = nodes[node_prev].right;
        }
        update(nodes[node_prev].left, nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right != -1) {
            int ln = nodes[nodes[node].right].left, rn = nodes[nodes[node].right].right;
            nodes[node].right = idx;
            nodes[idx] = Node();
            nodes[idx].left = ln, nodes[idx].right = rn;
            idx++;
        } else {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        if (nodes[node].left == -1) {
            nodes[node].left = nodes[node_prev].left;
        }
        update(nodes[node_prev].right, nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = nodes[nodes[node].left].val + nodes[nodes[node].right].val;
    return;
}

int query(int node_l, int node_r, int l, int r, int lq, int rq) {
    if (lq > r || rq < l) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node_r].val - nodes[node_l].val;
    }
    int mid = (l + r) / 2;
    return query(nodes[node_l].left, nodes[node_r].left, l, mid, lq, rq) + query(nodes[node_l].right, nodes[node_r].right, mid + 1, r, lq, rq);
}

int main() {
    IOS;
    sieve(N);
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    root[0] = idx;
    nodes[idx++] = Node();
    build(root[0], 0, N - 1);
    for (int i = 0; i < n; i++) {
        root[i + 1] = idx;
        nodes[idx++] = Node();
        int x = a[i];
        while (x > 1) {
            int e = 0, p = spf[x];
            while (x % p == 0) {
                e++;
                x /= p;
            }
            update(root[i], root[i + 1], 0, N - 1, p, e);
        }

    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        cout << query(root[l - 1], root[r], 0, N - 1, x, y) << endl;

    }
    return 0;
}
