//https://codeforces.com/contest/2107/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

set<int> adj[N];
set<int> nodes;

tuple<int, int, int> dist[N];
bool vis[N];
int parent[N];
vector<tuple<int, int, int>> ans;

void solve(int u) {
    vector<int> st{u};
    vis[u] = true;
    queue<int> q;
    q.push(u);
    dist[u] = make_tuple(1, u, u);
    while (q.size()) {
        int u = q.front();
        int d = get<0>(dist[u]);
        q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                st.push_back(v);
                dist[v] = make_tuple(d + 1, v, v);
                q.push(v);
            }
        }
    }
    tuple<int, int, int> best = make_tuple(0, 0, 0);
    for (int v : st) {
        if (dist[v] > best) {
            best = dist[v];
            u = v;
        }
        dist[v] = make_tuple(0, 0, 0);
        vis[v] = false;
    }

    vis[u] = true;
    q.push(u);
    dist[u] = make_tuple(1, u, u);
    while (q.size()) {
        int u = q.front();
        int d = get<0>(dist[u]);
        q.pop();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                dist[v] = make_tuple(d + 1, v, v);
                parent[v] = u;
                q.push(v);
            }
        }
    }
    best = make_tuple(0, 0, 0);
    for (int v : st) {
        if (dist[v] > best) {
            best = dist[v];
        }
        dist[v] = make_tuple(0, 0, 0);
        vis[v] = false;
    }
    int v = get<2>(best);
    vector<int> collect;
    while (v != u) {
        collect.push_back(v);
        v = parent[v];
    }
    collect.push_back(u);
    auto [D, U, V] = best;
    U = u;
    if (U < V) {
        swap(U, V);
    }
    ans.push_back(make_tuple(D, U + 1, V + 1));
    for (int x : collect) {
        vector<int> a;
        for (int y : adj[x]) {
            a.push_back(y);
        }
        for (int y : a) {
            adj[y].erase(x);
            adj[x].erase(y);
        }
        nodes.erase(x);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        for (int i = 0; i < n; i++) {
            nodes.insert(i);
        }
        while (nodes.size()) {
            int u = *nodes.begin();
            solve(u);
        }
        sort(ans.begin(), ans.end(), greater<tuple<int, int, int>>());
        for (auto [D, U, V]: ans) {
            cout << D << " "<< U << " " << V << " ";
        }
        cout << endl;
        ans.clear();
    }

    return 0;
}
