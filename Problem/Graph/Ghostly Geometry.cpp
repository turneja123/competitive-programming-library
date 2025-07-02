//https://ocpc2025s.eolymp.space/en/compete/1kvhss06dl7d13loo53cn0nk1k/problem/7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int color[N];
set<int> adj[N];
set<pair<int, int>> st;

int parent[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (adj[a].size() > adj[b].size()) {
        swap(a, b);
    }
    st.erase({adj[a].size(), a});
    st.erase({adj[b].size(), b});
    for (int v : adj[a]) {
        int s = adj[v].size();
        adj[v].erase(a);
        st.erase({s, v});
        adj[v].insert(b);
        adj[b].insert(v);
        s = adj[v].size();
        st.insert({s, v});
    }
    st.insert({adj[b].size(), b});
    parent[a] = b;
}


void calc() {
    if (st.empty()) {
        return;
    }
    auto [d, u] = *st.begin();
    vector<int> nei;
    if (d <= 4) {
        for (int v : adj[u]) {
            int s = adj[v].size();
            adj[v].erase(u);
            st.erase({s, v});
            s = adj[v].size();
            st.insert({s, v});
            nei.push_back(v);
        }
    } else {
        int p, q;
        for (int x : adj[u]) {
            for (int y : adj[u]) {
                if (x != y && adj[x].find(y) == adj[x].end()) {
                    p = x, q = y;
                }
            }
        }
        dsu_unite(p, q);
        for (int v : adj[u]) {
            int s = adj[v].size();
            adj[v].erase(u);
            st.erase({s, v});
            s = adj[v].size();
            st.insert({s, v});
            nei.push_back(v);
        }

    }
    st.erase({adj[u].size(), u});
    calc();
    vector<int> seen(6, 0);
    for (int v : nei) {
        seen[color[dsu_find(v)]] = 1;
    }
    for (int i = 1; i <= 5; i++) {
        if (!seen[i]) {
            color[u] = i;
            break;
        }
    }
    return;
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        parent[i] = i;
    }
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
        edges.push_back({u, v});
    }
    for (int i = 0; i < n; i++) {
        int s = adj[i].size();
        st.insert({s, i});
    }
    calc();
    for (int i = 0; i < n; i++) {
        color[i] = color[dsu_find(i)];
        assert(color[i]);
    }
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        int x = color[u], y = color[v];
        assert(x != y);
        if (x > y) {
            swap(x, y);
        }
        if (abs(x - y) == 1 || (x == 1 && y == 5)) {
            cout << 'R';
        } else {
            cout << 'B';
        }
    }
    return 0;
}
