//https://codeforces.com/problemset/problem/990/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int parent[N];
int a[N];
long long ans[N];
vector<int> adj[N];
map<int, int> mp[N];

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    for (auto [ga, cta] : mp[a]) {
        for (auto [gb, ctb] : mp[b]) {
            ans[__gcd(ga, gb)] += (long long)cta * ctb;
        }
    }
    for (auto [ga, cta] : mp[a]) {
        mp[b][ga] += cta;
    }
    parent[a] = b;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    ans[a[u]]++;
    mp[u][a[u]]++;
    for (int v : adj[u]) {
        if (v != p) {
            int x = dsu_find(u), y = dsu_find(v);
            map<int, int> nx;
            for (auto [g, ct] : mp[y]) {
                nx[__gcd(g, a[u])] += ct;
            }
            mp[y] = nx;
            dsu_merge(x, y);
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        parent[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 1; i < N; i++) {
        if (ans[i]) {
            cout << i << " " << ans[i] << endl;
        }
    }

    return 0;
}
