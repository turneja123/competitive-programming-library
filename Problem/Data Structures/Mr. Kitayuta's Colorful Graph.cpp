//https://codeforces.com/contest/506/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int parent[N];
int sz[N];
bool cpy[N];
int ans[N];
int seen[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

vector<int> colors[N];
vector<pair<int, int>> edges[N];
vector<int> ask[N];


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--, c--;
        edges[c].push_back({u, v});
        colors[u].push_back(c);
        colors[v].push_back(c);
    }
    for (int i = 0; i < n; i++) {
        if (colors[i].size()) {
            sort(colors[i].begin(), colors[i].end());
            colors[i].erase(unique(colors[i].begin(), colors[i].end()), colors[i].end());
        }
    }
    cin >> q;
    map<pair<int, int>, int> mp;
    vector<pair<int, int>> qe(q);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (colors[u].size() > colors[v].size() || (colors[u].size() == colors[v].size() && u > v)) {
            swap(u, v);
        }
        qe[i] = {u, v};
        if (mp.find({u, v}) != mp.end()) {
            cpy[i] = true;
            continue;
        }
        mp[{u, v}] = 0;
        for (int c : colors[u]) {
            ask[c].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        vector<int> restore;
        for (auto [u, v] : edges[i]) {
            if (!seen[u]) {
                seen[u] = true;
                restore.push_back(u);
            }
            if (!seen[v]) {
                seen[v] = true;
                restore.push_back(v);
            }
            u = dsu_find(u), v = dsu_find(v);
            if (u != v) {
                dsu_unite(u, v);
            }
        }
        for (int j : ask[i]) {
            auto [u, v] = qe[j];
            if (dsu_find(u) == dsu_find(v)) {
                ans[j]++;
            }
        }
        for (int u : restore) {
            parent[u] = u;
            sz[u] = 1;
            seen[u] = false;
        }
    }


    for (int i = 0; i < q; i++) {
        auto [u, v] = qe[i];
        if (!cpy[i]) {
            cout << ans[i] << endl;
            mp[{u, v}] = ans[i];
        } else {
            cout << mp[{u, v}] << endl;
        }
    }



    return 0;
}
