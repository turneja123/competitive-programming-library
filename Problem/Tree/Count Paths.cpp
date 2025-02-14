//https://codeforces.com/contest/1923/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int c[N];
int parent[N];
vector<int> adj[N];
map<int, int> st[N];

long long ans = 0;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it : st[a]) {
        auto f = st[b].find(it.first);
        if (f != st[b].end()) {
            ans += (long long)it.second * f->second;
        }
    }

    for (auto it : st[a]) {
        st[b][it.first] += it.second;
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            auto it = st[b].find(c[u]);
            if (it != st[b].end()) {
                ans += it->second;
                st[b].erase(it);
            }
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    st[a][c[u]]++;
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        dfs(0, -1);
        cout << ans << endl;
        ans = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[i].clear();
        }
    }
    return 0;
}
