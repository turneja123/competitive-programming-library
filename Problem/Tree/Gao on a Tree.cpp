//https://www.spoj.com/problems/GOT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<vector<int>> paths;
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;
vector<int> adj[N];
int vals[N];
int parent[N];
int sz[N];
int tail[N];
pair<int, int> pos[N];
bool head[N];
int edges[N];
int qans[N];

vector<int> colors[N];

pair<pair<int, int>, pair<int, int>> queries[N];

int dfs(int v, int p, int ct) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            parent[u] = v;
            ct += dfs(u, v, 1);
        }
    }
    tout[v] = ++timer;
    return sz[v] = ct;
}

void dfs_markedges(int v, int p) {
    for (int u : adj[v]) {
        if (u != p) {
            if (sz[u] >= sz[v] / 2 + sz[v] % 2) {
                edges[u] = 1;
                head[v] = false;
            } else {
                edges[u] = 0;
            }
            dfs_markedges(u, v);
        }
    }
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

vector<int> segtree[N];

int query(int l, int r, int lq, int rq, int node, int n) {
    if (l > rq || r < lq || lq > rq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[n][node];
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, n) + query(mid + 1, r, lq, rq, 2 * node + 2, n);
}

void update(int l, int r, int ind, int val, int node, int n) {
    if (l == r) {
        segtree[n][node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, n);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, n);
    }
    segtree[n][node] = segtree[n][2 * node + 1] + segtree[n][2 * node + 2];
}


void build(int l, int r, int node, int n) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[n][node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, n);
    build(mid + 1, r, 2 * node + 2, n);
    segtree[n][node] = 0;
}

int calc(int a, int b, int flag) {
    int ans = 0;
    while (1) {
        int j = pos[a].first;
        if (j == pos[b].first) {
            ans += query(0, paths[j].size() - 1, pos[a].second, pos[b].second - flag, 0, j);
            break;
        }
        ans += query(0, paths[j].size() - 1, pos[a].second, paths[j].size() - 1, 0, j);
        a = parent[tail[a]];
    }
    return ans;
}


int main() {
    IOS;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        int n, q;
        iss >> n >> q;
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        tin.resize(n);
        tout.resize(n);

        getline(cin, line);
        istringstream is(line);
        for (int i = 0; i < n; i++) {
            is >> vals[i];
            if (vals[i] <= n) {
                colors[vals[i]].push_back(i);
            }
            head[i] = true;
        }

        for (int i = 0; i < n - 1; i++) {
            getline(cin, line);
            istringstream iss(line);
            int u, v;
            iss >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < q; i++) {
            getline(cin, line);
            istringstream iss(line);
            int u, v, c;
            iss >> u >> v >> c;
            u--, v--;
            queries[i] = make_pair(make_pair(c, i), make_pair(u, v));
        }
        sort(queries, queries + q);

        dfs(0, 0, 1);
        dfs_markedges(0, 0);
        for (int i = 0; i < n; i++) {
            if (head[i]) {
                vector<int> path;
                int v = i;
                while (1) {
                    path.push_back(v);
                    if (edges[v] == 0) {
                        break;
                    }
                    v = parent[v];
                }
                for (int i = 0; i < path.size(); i++) {
                    tail[path[i]] = path[path.size() - 1];
                    pos[path[i]] = {paths.size(), i};
                }
                paths.push_back(path);
            }
        }

        for (int i = 0; i < paths.size(); i++) {
            segtree[i].resize(4 * paths[i].size());
            build(0, paths[i].size() - 1, 0, i);
        }
        for (int i = 0; i < q; i++) {
            int c = get<0>(queries[i]).first, u = get<1>(queries[i]).first, v = get<1>(queries[i]).second;
            if (i == 0) {
                for (int x : colors[c]) {
                    int j = pos[x].first;
                    update(0, paths[j].size() - 1, pos[x].second, 1, 0, j);
                }
            } else {
                int c_prev = get<0>(queries[i - 1]).first;
                if (c != c_prev) {
                    for (int x : colors[c]) {
                        int j = pos[x].first;
                        update(0, paths[j].size() - 1, pos[x].second, 1, 0, j);
                    }
                    for (int x : colors[c_prev]) {
                        int j = pos[x].first;
                        update(0, paths[j].size() - 1, pos[x].second, 0, 0, j);
                    }
                }
            }
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            int ans = calc(v, l, 0);
            if (u != l) {
                ans += calc(u, l, 1);
            }
            if (ans > 0) {
                qans[get<0>(queries[i]).second] = 1;
            } else {
                qans[get<0>(queries[i]).second] = 0;
            }

        }
        for (int i = 0; i < q; i++) {
            if (qans[i] == 0) {
                cout << "NotFind" << endl;
            } else {
                cout << "Find" << endl;
            }
        }
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            colors[i].clear();
            segtree[i].clear();

        }
        up.clear();
        tin.clear();
        tout.clear();
        paths.clear();
        timer = 0;
        cout << endl;
    }
    return 0;
}
