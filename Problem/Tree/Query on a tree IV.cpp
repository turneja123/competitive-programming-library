//https://www.spoj.com/problems/QTREE4/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

vector<pair<int, int>> adj[N];
vector<int> dist[N];

int seen_c[N];
int sz[N];
int depth[N];

int par_c[N];
int lev[N];

struct LazyPQ {
    priority_queue<int> pq;
    priority_queue<int> deleted;

    void clean() {
        while (pq.size() && deleted.size() && pq.top() == deleted.top()) {
            pq.pop();
            deleted.pop();
        }
    }

    void insert(int x) {
        if (x == -INF) {
            return;
        }
        pq.push(x);
    }

    void erase(int x) {
        if (x == -INF) {
            return;
        }
        deleted.push(x);
    }

    int get_max() {
        clean();
        if (pq.empty()) {
            return -INF;
        }
        return pq.top();
    }

    int sum_two() {
        clean();
        if (pq.empty()) {
            return -INF;
        }
        int fi = pq.top();
        pq.pop();
        clean();
        if (pq.empty()) {
            pq.push(fi);
            return -INF;
        }
        int se = pq.top();
        pq.push(fi);
        return fi + se;
    }
};

LazyPQ bests[N];
LazyPQ bests_from[N];
LazyPQ glob;

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs_cen(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && 2 * sz[v] > n) {
            return dfs_cen(v, u, n);
        }
    }
    return u;
}

void dfs(int u, int p) {
    dist[u].push_back(depth[u]);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + wt;
            dfs(v, u);
        }
    }
}

void build(int u, int k, int p) {
    dfs_sz(u, u);
    int c = dfs_cen(u, u, sz[u]);
    par_c[c] = p;
    depth[c] = 0;
    lev[c] = k;
    dist[c].push_back(0);
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = depth[c] + wt;
            dfs(v, c);
        }
    }
    seen_c[c] = 1;
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build(v, k + 1, c);
        }
    }
}

void add(int u) {
    int k = lev[u];
    int c = u;
    glob.erase(bests[c].sum_two());
    bests[c].insert(0);
    glob.insert(bests[c].sum_two());

    while (1) {
        k--;
        if (k < 0) {
            break;
        }
        int prev = c;
        c = par_c[c];
        glob.erase(bests[c].sum_two());
        bests[c].erase(bests_from[prev].get_max());
        //glob.insert(bests[c].sum_two());

        bests_from[prev].insert(dist[u][k]);

        //glob.erase(bests[c].sum_two());
        bests[c].insert(bests_from[prev].get_max());
        glob.insert(bests[c].sum_two());
    }
}

void del(int u) {
    int k = lev[u];
    int c = u;
    glob.erase(bests[c].sum_two());
    bests[c].erase(0);
    glob.insert(bests[c].sum_two());

    while (1) {
        k--;
        if (k < 0) {
            break;
        }
        int prev = c;
        c = par_c[c];
        glob.erase(bests[c].sum_two());
        bests[c].erase(bests_from[prev].get_max());
        //glob.insert(bests[c].sum_two());

        bests_from[prev].erase(dist[u][k]);

        //glob.erase(bests[c].sum_two());
        bests[c].insert(bests_from[prev].get_max());
        glob.insert(bests[c].sum_two());
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    build(0, 0, -1);
    int ct = 0;
    vector<int> col(n, 0);
    for (int i = 0; i < n; i++) {
        add(i);
        col[i] = 1;
        ct++;
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        char t;
        cin >> t;
        if (t == 'C') {
            int u;
            cin >> u;
            u--;
            if (col[u] == 0) {
                ct++;
                add(u);
                col[u] = 1;
            } else {
                ct--;
                del(u);
                col[u] = 0;
            }
        } else {
            if (ct == 0) {
                cout << "They have disappeared." << endl;
            } else {
                cout << max(0, glob.get_max()) << endl;
            }
        }
    }


    return 0;
}
