//https://dmoj.ca/problem/dmopc17c5p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 4e6 + 5;
const int K = 30;

struct Node {
    int left;
    int right;
    vector<int> v;
    Node() : left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int a[N];
int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

int dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (a == b) {
        return a;
    }
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
    return a;
}

void query(int node, int d, int x, int m, int j) {
    if (d == -1) {
        nodes[node].v.push_back(j);
        return;
    }
    int cx = x & (1 << d), cm = m & (1 << d);
    if (cx == 0 && cm == 0) {
        if (nodes[node].left != -1) {
            query(nodes[node].left, d - 1, x, m, j);
        }
    } else if (cx == 0 && cm != 0) {
        if (nodes[node].left != -1) {
            nodes[nodes[node].left].v.push_back(j);
        }
        if (nodes[node].right != -1) {
            query(nodes[node].right, d - 1, x, m, j);
        }
    } else if (cx != 0 && cm == 0) {
        if (nodes[node].right != -1) {
            query(nodes[node].right, d - 1, x, m, j);
        }
    } else {
        if (nodes[node].right != -1) {
            nodes[nodes[node].right].v.push_back(j);
        }
        if (nodes[node].left != -1) {
            query(nodes[node].left, d - 1, x, m, j);
        }
    }
}

void add(int node, int d, int val, int j) {
    if (d < 0) {
        nodes[node].v.push_back(j);
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].left, d - 1, val, j);
        return;
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        add(nodes[node].right, d - 1, val, j);
        return;
    }
}

void dfs(int node, int parent) {
    for (int i = 0; i < nodes[node].v.size(); i++) {
        if (parent == -1) {
            parent = dsu_find(nodes[node].v[i]);
        } else {
            parent = dsu_unite(parent, nodes[node].v[i]);
        }
    }
    if (nodes[node].left != -1) {
        dfs(nodes[node].left, parent);
    }
    if (nodes[node].right != -1) {
        dfs(nodes[node].right, parent);
    }
}

int main() {
    IOS;
    nodes[idx++] = Node();
    int n, q, m;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        add(0, K - 1, a[i], i);
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        query(0, K - 1, a[i], m, i);
    }
    dfs(0, -1);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        u = dsu_find(u), v = dsu_find(v);
        if (u == v) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
