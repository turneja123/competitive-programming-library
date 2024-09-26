//https://www.spoj.com/problems/LISTREE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int MAX = 4e7;

vector<int> adj[N];

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int parent[N];
set<int> st[N];
int ans = 1;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq || lq > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (nodes[node].left != -1) {
        ans = max(ans, query(nodes[node].left, l, mid, lq, rq));
    }
    if (nodes[node].right != -1) {
        ans = max(ans, query(nodes[node].right, mid + 1, r, lq, rq));
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val = max(nodes[node].val, val);
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
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].left].val);
    }
    if (nodes[node].right != -1) {
        nodes[node].val = max(nodes[node].val, nodes[nodes[node].right].val);
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
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    ans = max(ans, query(2 * a, 0, N - 1, 0, u - 1) + 1 + query(2 * b + 1, 0, N - 1, u + 1, N - 1));
    ans = max(ans, query(2 * b, 0, N - 1, 0, u - 1) + 1 + query(2 * a + 1, 0, N - 1, u + 1, N - 1));
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        ans = max(ans, query(2 * a, 0, N - 1, *it, *it) + query(2 * b + 1, 0, N - 1, *it + 1, N - 1));
        ans = max(ans, query(2 * a + 1, 0, N - 1, *it, *it) + query(2 * b, 0, N - 1, 0, *it - 1));
    }
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
        update(2 * b, 0, N - 1, *it, query(2 * a, 0, N - 1, *it, *it));
        update(2 * b + 1, 0, N - 1, *it, query(2 * a + 1, 0, N - 1, *it, *it));
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
    int a = dsu_find(u);
    update(2 * a, 0, N - 1, u, query(2 * a, 0, N - 1, 0, u - 1) + 1);
    update(2 * a + 1, 0, N - 1, u, query(2 * a + 1, 0, N - 1, u + 1, N - 1) + 1);
    st[a].insert(u);
    return;
}

int main(){
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            nodes[idx++] = Node();
            nodes[idx++] = Node();
        }
        dfs(0, 0);
        cout << ans << endl;
        ans = 1, idx = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[i].clear();
        }
    }

    return 0;
}
