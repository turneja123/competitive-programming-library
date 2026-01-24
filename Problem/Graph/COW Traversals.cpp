//https://usaco.org/index.php?page=viewproblem2&cpid=1545
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> go[N];

int ans[4];

int parent[N];
int sz[N];
int val[N];
vector<int> adj[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (a == b) {
        return;
    }

    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

vector<int> nodes;

void dfs(int u) {
    nodes.push_back(u);
    for (int v : adj[u]) {
        dfs(v);
    }
}

int main() {
    IOS;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        go[i] = {p, 0};
    }
    int q;
    cin >> q;
    vector<tuple<int, int, int>> restore;
    for (int i = 0; i < q; i++) {
        int u; char c;
        cin >> u >> c;
        u--;
        int t;
        if (c == 'C') {
            t = 1;
        } else if (c == 'O') {
            t = 2;
        } else {
            t = 3;
        }
        restore.push_back(make_tuple(u, go[u].first, go[u].second));
        go[u] = {u, t};
    }
    for (int i = 0; i < n; i++) {
        if (go[i].first != i) {
            adj[go[i].first].push_back(i);
        }
        sz[i] = 1;
        parent[i] = i;
    }
    for (int i = 0; i < n; i++) {
        if (go[i].first == i) {
            val[i] = go[i].second;
            dfs(i);
            for (int j = 1; j < nodes.size(); j++) {
                dsu_unite(dsu_find(i), dsu_find(nodes[j]));
                int a = dsu_find(i);
                val[a] = go[i].second;
            }
            ans[go[i].second] += sz[dsu_find(i)];
            nodes.clear();
        }
    }
    vector<tuple<int, int, int>> out;
    reverse(restore.begin(), restore.end());
    for (auto [u, v, t] : restore) {
        out.push_back({ans[1], ans[2], ans[3]});
        if (go[u].first == u && v == u) {
            int a = dsu_find(u);
            ans[val[a]] -= sz[a];
            val[a] = t;
            ans[val[a]] += sz[a];
        } else {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                ans[val[a]] -= sz[a];
                ans[val[b]] -= sz[b];
                int old = val[b];
                dsu_unite(a, b);
                a = dsu_find(u);
                val[a] = old;
                ans[val[a]] += sz[a];
            } else {
                ans[val[a]] -= sz[a];
                val[a] = 0;
                sz[a] = 0;
            }
        }
        go[u] = {v, t};
    }
    reverse(out.begin(), out.end());
    for (auto [x, y, z] : out) {
        cout << x << " " << y << " "<< z << endl;
    }



    return 0;
}
