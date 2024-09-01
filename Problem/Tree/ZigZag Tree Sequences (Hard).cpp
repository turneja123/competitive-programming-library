//https://www.codechef.com/problems/ZIGZAGTREE2?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 3e7 + 5;
const long long M = 1e9 + 7;

vector<int> adj[N];
set<int> st[2][N];
int vals[N];
int parent[N];

struct Node {
    long long val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

int root[2][N];
Node nodes[MAX];
int idx = 0;

long long ans = 0;

long long query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, sum = 0;
    if (nodes[node].left != -1) {
        sum += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        sum += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return sum % M;

}

void update(int node, int l, int r, int ind, long long val) {
    if (l == r) {
        nodes[node].val = (nodes[node].val + val) % M;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind, val);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind, val);
    }
    nodes[node].val = 0;
    if (nodes[node].left != -1) {
        nodes[node].val = (nodes[node].val + nodes[nodes[node].left].val) % M;
    }
    if (nodes[node].right != -1) {
        nodes[node].val = (nodes[node].val + nodes[nodes[node].right].val) % M;
    }
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int u) {
    if (st[0][a].size() + st[1][a].size() > st[0][b].size() + st[1][b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (int x : st[0][a]) {
        ans += query(root[1][b], 0, N - 1, x + 1, N - 1) * query(root[0][a], 0, N - 1, x, x) % M;
        ans %= M;

    }
    ans = (ans + query(root[0][b], 0, N - 1, 0, vals[u] - 1) * query(root[0][a], 0, N - 1, 0, vals[u] - 1) % M) % M;
    for (int x : st[1][a]) {
        ans += query(root[0][b], 0, N - 1, 0, x - 1) * query(root[1][a], 0, N - 1, x, x) % M;
        ans %= M;
    }
    ans = (ans + query(root[1][b], 0, N - 1, vals[u] + 1, N - 1) * query(root[1][a], 0, N - 1, vals[u] + 1, N - 1) % M) % M;
    for (int x : st[0][a]) {
        update(root[0][b], 0, N - 1, x, query(root[0][a], 0, N - 1, x, x));
        st[0][b].insert(x);
    }
    for (int x : st[1][a]) {
        update(root[1][b], 0, N - 1, x, query(root[1][a], 0, N - 1, x, x));
        st[1][b].insert(x);
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }

    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    int par = dsu_find(u);
    long long x = query(root[0][par], 0, N - 1, 0, vals[u] - 1);
    ans = (ans + x) % M;
    update(root[1][par], 0, N - 1, vals[u], x + 1);
    x = query(root[1][par], 0, N - 1, vals[u] + 1, N - 1);
    ans = (ans + x) % M;
    update(root[0][par], 0, N - 1, vals[u], x + 1);
    st[0][par].insert(vals[u]);
    st[1][par].insert(vals[u]);
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> vals[i];
        }
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            root[0][i] = idx;
            nodes[idx++] = Node();
            root[1][i] = idx;
            nodes[idx++] = Node();
        }
        dfs(0, -1);
        cout << ans << endl;
        idx = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[0][i].clear();
            st[1][i].clear();
        }
        ans = 0;
    }

    return 0;
}
