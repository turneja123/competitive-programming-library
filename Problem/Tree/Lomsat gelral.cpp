//https://codeforces.com/contest/600/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

long long a[N];
long long ans[N];
long long mx[N];
int parent[N];
long long sum[N];
vector<int> adj[N];
map<int, long long> mp[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        long long c = it->first, ct = it->second;
        if (mp[b].find(c) == mp[b].end()) {
            mp[b][c] = ct;
        } else {
            mp[b][c] += ct;
        }
        if (mp[b][c] > mx[b]) {
            mx[b] = mp[b][c];
            sum[b] = c;
        } else if (mp[b][c] == mx[b]) {
            sum[b] += c;
        }
    }
    return;
}

void dfs(int u, int p) {
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            child.push_back(v);
        }
    }
    for (int v : child) {
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_merge(a, b);
        }
    }
    ans[u] = sum[dsu_find(u)];
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
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
        mp[i][a[i]]++;
        sum[i] = a[i];
        mx[i] = 1;
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
