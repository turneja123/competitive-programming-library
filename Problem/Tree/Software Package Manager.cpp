//https://dmoj.ca/problem/noi15p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> adj[N];
int sz[N];
int depth[N];
int up[N];
int id[N];
int pos[N];
int head[N];


struct Node {
    int ct[2];
    int setVal;
    int sentinel;

    Node() {
        sentinel = 1;
        setVal = -1;
    }

    Node(int x) {
        ct[x] = 1;
        ct[x ^ 1] = 0;
        sentinel = 0;
        setVal = -1;
    }

};

Node combine(Node left, Node right) {
    if (left.sentinel) {
        return right;
    }
    if (right.sentinel) {
        return left;
    }
    Node node;
    node.sentinel = 0;
    node.ct[0] = left.ct[0] + right.ct[0];
    node.ct[1] = left.ct[1] + right.ct[1];
    return node;
}

struct Segtree {
    int n;
    vector<Node> nodes;

    Segtree() {

    }

    Segtree(int _n) {
        n = _n;
        nodes.resize(4 * n);
        build(0, n - 1, 0);
    }

    void apply(int l, int r, int node) {
        int x = nodes[node].setVal;
        if (x == -1) {
            return;
        }
        nodes[node].ct[x] = r - l + 1;
        nodes[node].ct[x ^ 1] = 0;

        if (l != r) {
            nodes[2 * node + 1].setVal = x;
            nodes[2 * node + 2].setVal = x;
        }
        nodes[node].setVal = -1;
    }

    void upd(int l, int r, int node, int lq, int rq, int val) {
        if (l > rq || r < lq || l > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            nodes[node].setVal = val;
            return;
        }
        apply(l, r, node);
        int mid = (l + r) / 2;
        upd(l, mid, 2 * node + 1, lq, rq, val);
        upd(mid + 1, r, 2 * node + 2, lq, rq, val);
        apply(l, mid, 2 * node + 1);
        apply(mid + 1, r, 2 * node + 2);
        nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
        return;
    }

    Node query(int l, int r, int node, int lq, int rq) {
        if (l > rq || r < lq || l > r) {
            Node sentinel;
            return sentinel;
        }
        apply(l, r, node);
        if (l >= lq && r <= rq) {
            return nodes[node];
        }
        int mid = (l + r) / 2;
        return combine(query(l, mid, 2 * node + 1, lq, rq), query(mid + 1, r, 2 * node + 2, lq, rq));
    }

    void build(int l, int r, int node) {
        if (l == r) {
            nodes[node] = Node(0);
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, 2 * node + 1);
        build(mid + 1, r, 2 * node + 2);
        nodes[node] = combine(nodes[2 * node + 1], nodes[2 * node + 2]);
    }



};

vector<vector<int>> paths;
Segtree segtree;

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            up[v] = u;
            depth[v] = depth[u] + 1;
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int timer = 0;

void dfs_hld(int u, int p) {
    pos[u] = timer++;
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            child.push_back(v);
        }
    }
    if (child.empty()) {
        return;
    }
    sort(child.begin(), child.end(), [&](int a, int b) {return sz[a] > sz[b];});
    for (int v : child) {
        if (2 * sz[v] >= sz[u]) {
            head[v] = 0;
        }
        dfs_hld(v, u);
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        head[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    dfs_sz(0, 0);
    dfs_hld(0, 0);

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {return depth[a] > depth[b];});
    vector<int> vis(n, 0);
    int m = 0;
    for (int i = 0; i < n; i++) {
        int u = ord[i];
        if (vis[u]) {
            continue;
        }
        vector<int> path;
        while (1) {
            vis[u] = 1;
            id[u] = m;
            path.push_back(u);
            if (head[u]) {
                break;
            }
            u = up[u];
        }
        m++;
        paths.push_back(path);
    }
    segtree = Segtree(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string s;
        cin >> s;
        int u;
        cin >> u;
        int val = (s == "install" ? 1 : 0);
        int ans = 0;

        if (val == 1) {
            while (1) {
                Node node;
                int j = id[u];
                int v = paths[j].back();

                int l = pos[v], r = pos[u];

                Node cur = segtree.query(0, n - 1, 0, l, r);
                ans += cur.ct[val ^ 1];
                segtree.upd(0, n - 1, 0, l, r, val);

                if (id[u] == id[0]) {
                    break;
                }

                u = up[v];
            }
        } else {
            Node node = segtree.query(0, n - 1, 0, pos[u], pos[u] + sz[u] - 1);
            ans = node.ct[val ^ 1];
            segtree.upd(0, n - 1, 0, pos[u], pos[u] + sz[u] - 1, 0);
        }
        cout << ans << endl;
    }


    return 0;
}
