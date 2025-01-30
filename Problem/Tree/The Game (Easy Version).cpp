//https://codeforces.com/contest/2062/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int R = 4e5 + 5;
const int MAX = 3e7 + 5;

int a[N];
int ans;
int pref[N];
int parent[N];
int ct[N];

map<int, int> mp[N];
vector<int> adj[N];

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
        mp[b][it->first] += it->second;
        if (mp[b][it->first] == ct[it->first]) {
            update(b, 0, R - 1, it->first, 1);
        }
    }
    mp[a].clear();
    return;
}

void dfs(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
        }
    }
    mp[u][a[u]]++;
    if (mp[u][a[u]] == ct[a[u]]) {
        update(u, 0, R - 1, a[u], 1);
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    int x = dsu_find(u);
    int y = query(x, 0, R - 1, a[u] + 1, n);
    if (pref[n] - pref[a[u]] - y > 0) {
        if (ans == -1) {
            ans = u;
        } else if (a[ans] < a[u]) {
            ans = u;
        }
    }
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
            cin >> a[i];
            ct[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1];
            if (ct[i] != 0) {
                pref[i]++;
            }
        }
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
        }
        ans = -1;
        dfs(0, 0, n);
        cout << ans + 1 << endl;
        for (int i = 0; i <= n; i++) {
            mp[i].clear();
            adj[i].clear();
            ct[i] = 0;
            pref[i] = 0;
        }
        idx = 0;
    }

    return 0;
}
