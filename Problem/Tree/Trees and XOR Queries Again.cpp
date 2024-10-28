//https://codeforces.com/contest/1902/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const int K = 20;

int vals[N];

class Basis {
public:
    vector<int> basis;
    vector<int> node;

    Basis() : basis(vector<int>(K, 0)), node(vector<int>()) {}

    vector<int> get_basis() {
        return basis;
    }

    vector<int> get_node() {
        return node;
    }

    void insert_vector(int a, int j) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                basis[i] = a;
                node.push_back(j);
                return;
            }
            a ^= basis[i];
        }
        return;
    }

    bool exists(long long a) {
        for (int i = K - 1; i >= 0; i--) {
            int c = a & (1 << i);
            if (!c) {
                continue;
            }
            if (!basis[i]) {
                return false;
            }
            a ^= basis[i];
        }
        return true;
    }

    void inherit(Basis &b, int a, int j) {
        vector<int> parent_node = b.get_node();
        insert_vector(a, j);
        for (int i = 0; i < parent_node.size(); i++) {
            insert_vector(vals[parent_node[i]], parent_node[i]);
        }
        return;
    }
};

Basis b[N];

vector<int> adj[N];
int up[K][N];
int depth[N];

void dfs(int u, int p) {
    if (u == 0) {
        b[u].insert_vector(vals[u], u);
    } else {
        b[u].inherit(b[p], vals[u], u);
    }
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    return;
}

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}



int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v; long long x;
        cin >> u >> v >> x;
        u--, v--;
        Basis cur;
        int l = lca(u, v);
        if (u != l) {
            vector<int> node = b[u].get_node();
            for (int i = 0; i < node.size(); i++) {
                if (depth[node[i]] > depth[l]) {
                    cur.insert_vector(vals[node[i]], node[i]);
                }
            }
        }
        if (v != l) {
            vector<int> node = b[v].get_node();
            for (int i = 0; i < node.size(); i++) {
                if (depth[node[i]] > depth[l]) {
                    cur.insert_vector(vals[node[i]], node[i]);
                }
            }
        }

        cur.insert_vector(vals[l], l);

        if (cur.exists(x)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
