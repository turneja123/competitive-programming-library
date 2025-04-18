//https://dmoj.ca/problem/aac2p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;
const int B = 1000;

vector<int> adj[N];
vector<int> child[N];
int tour[2 * N];

int depth[N];
int pos[N];
int timer = 0;
int table[K][2 * N];
int mn[K][2 * N];
int color[N];
int subtree[N];
int parent[N];
long long save[N];

bool comp(int a, int b) {
    return pos[a] > pos[b];
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        int u = tour[i - 1];
        table[0][i] = depth[u];
        mn[0][i] = u;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] < table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] < table[k][r - (1 << k) + 1]) {
        return mn[k][l];
    }
    return mn[k][r - (1 << k) + 1];
}

int lca(int a, int b) {
    int l = pos[a];
    int r = pos[b];
    if (l > r) {
        swap(l, r);
    }
    return query(l, r);
}

void dfs(int u, int p) {
    pos[u] = timer;
    tour[timer++] = u;
    for (int v : adj[u]) {
        if (v != p) {
            child[u].push_back(v);
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour[timer++] = u;
        }
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    build(2 * n - 1);
    vector<int> nodes;
    for (int i = 0; i < n; i++) {
        nodes.push_back(i);
    }
    sort(nodes.begin(), nodes.end(), comp);
    for (int i = 0; i < q; i++) {
        int m;
        cin >> m;
        vector<int> a(m);
        for (int j = 0; j < m; j++) {
            cin >> a[j];
            a[j]--;
        }
        if (m < B) {
            int best = 1e9;
            for (int j = 0; j < m; j++) {
                int cur = 0;
                for (int k = 0; k < m; k++) {
                    int l = lca(a[j], a[k]);
                    cur += depth[a[k]] - depth[l];
                }
                best = min(best, cur);
            }
            cout << best << endl;
        } else {
            long long ans = 0;
            for (int u : a) {
                color[u] = 1;
                ans += depth[u];
            }
            long long best = 0;
            for (int u : nodes) {
                subtree[u] = color[u];
                save[u] = 0;
                for (int v : child[u]) {
                    subtree[u] += subtree[v];
                    save[u] = max(save[u], save[v] + subtree[v]);
                }
            }
            for (int i = 0; i < n; i++) {
                best = max(best, save[i]);
                color[i] = 0;
            }
            cout << ans - best << endl;
        }
    }
    return 0;
}
