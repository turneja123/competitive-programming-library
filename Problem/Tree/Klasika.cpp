//https://dmoj.ca/problem/coci19c4p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;
const int MAX = 3e7 + 5;

struct Node {
    int tim;
    int left;
    int right;
    Node() : tim(N), left(-1), right(-1) {}
};

vector<int> adj[N];

int path[N];
int timer[N];
int val[N];

vector<tuple<int, int, int>> queries_dsu[N];
set<pair<int, int>> st[N];
int parent[N];
int ans[N];

Node nodes[MAX];
int idx = 0;

int query(int node, int d, int val, int ans, int tim) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].right != -1 && nodes[nodes[node].right].tim < tim) {
            return query(nodes[node].right, d - 1, val, ans ^ (1 << d), tim);
        } else {
            return query(nodes[node].left, d - 1, val, ans, tim);
        }
    } else {
        if (nodes[node].left != -1 && nodes[nodes[node].left].tim < tim) {
            return query(nodes[node].left, d - 1, val, ans ^ (1 << d), tim);
        } else {
            return query(nodes[node].right, d - 1, val, ans, tim);
        }
    }
}

void add(int node, int d, int val, int tim) {
    if (d < 0) {
        nodes[node].tim = min(nodes[node].tim, tim);
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val, tim);
        nodes[node].tim = min(nodes[node].tim, nodes[nodes[node].left].tim);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val, tim);
        nodes[node].tim = min(nodes[node].tim, nodes[nodes[node].right].tim);
        return;
    }
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            path[v] = path[u] ^ val[v];
            dfs(v, u);
        }
    }
    return;
}


int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
        add(b, 30, it->first, it->second);
    }
    return;
}

void dfs_dsu(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs_dsu(v, u);
        }
    }
    st[u].insert(make_pair(path[u], timer[u]));
    add(u, 30, path[u], timer[u]);
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    for (int i = 0; i < queries_dsu[u].size(); i++) {
        auto [t, x, ind] = queries_dsu[u][i];
        ans[ind] = query(a, 30, x, 0, t);
    }

    return;
}

int main() {
    IOS;
    int q, n = 1;
    cin >> q;
    vector<tuple<int, int, int>> queries;\
    timer[0] = -1;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        if (s == "Add") {
            int u, x;
            cin >> u >> x;
            u--;
            adj[u].push_back(n);
            adj[n].push_back(u);
            timer[n] = i;
            val[n] = x;
            n++;
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            queries.push_back(make_tuple(i, u, v));
        }
    }
    dfs(0, 0);
    for (int i = 0; i < queries.size(); i++) {
        auto [t, u, v] = queries[i];
        queries_dsu[v].push_back(make_tuple(t, path[u], i));
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        nodes[idx++] = Node();
    }
    dfs_dsu(0, 0);
    for (int i = 0; i < queries.size(); i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
