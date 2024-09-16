//https://dmoj.ca/problem/lemontree
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int R = 2e8 + 5;
const int MAX = 1e7 + 5;

int val[N];
int parent[N];
int depth[N];
vector<int> adj[N];
map<int, int> mp[N];

long long ans = 0;

struct Node {
    int val;
    int left;
    int right;
    Node() : val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;

int query(int node, int l, int r, int lq, int rq) {
    if (r < lq || l > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return nodes[node].val;
    }
    int mid = (l + r) / 2, ans = 0;
    if (r - l == 1 && mid == r) {
        mid--;
    }
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq);
    }
    return ans;

}

void update(int node, int l, int r, int ind, int val) {
    if (l == r) {
        nodes[node].val += val;
        return;
    }
    int mid = (l + r) / 2;
    if (r - l == 1 && mid == r) {
        mid--;
    }
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
        nodes[node].val += nodes[nodes[node].left].val;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
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
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        int x = 2 * depth[u] - val[u] - it->first;
        ans += (long long)query(b, -(R - 1), R - 1, -(R - 1), x - 1) * it->second;
    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] += it->second;
        update(b, -(R - 1), R - 1, it->first, it->second);
    }
    return;
}

void dfs(int u, int p) {
    depth[u] += val[u];
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u];
            dfs(v, u);
        }
    }
    mp[u][depth[u]]++;
    update(u, -(R - 1), R - 1, depth[u], 1);
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }

    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        nodes[idx++] = Node();
        cin >> val[i];
        val[i] -= m + 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    cout << ans;


    return 0;
}
