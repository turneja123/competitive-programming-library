//https://codesprintla26.kattis.com/contests/codesprintla26open/problems/sorcerersrift
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int sz[N];
int seen_c[N];
vector<int> adj[N];


void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

void build(int U, int p, int other, int &ans) {
    rep:dfs_subtree(U, U);
    int c = dfs_centroid(U, U, sz[U]);
    if (p == -1) {
        p = c;
    }
    seen_c[c] = true;

    vector<pair<int, int>> subs;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs(v, v);
            subs.push_back({-sz[v], v});
        }
    }
    if (subs.empty()) {
        ans = c;
        return;
    }
    sort(subs.begin(), subs.end());
    if (subs.size() == 1) {
        int u = subs[0].second;
        cout << "? " << c + 1 << " " << u + 1 << " " << c + 1 << " " << other << endl;
        int k;
        cin >> k;
        if (k == 1) {
            ans = c;
            return;
        } else {
            ans = u;
            return;
        }
    } else {
        int u = subs[0].second, v = subs[1].second;
        cout << "? " << c + 1 << " " << u + 1 << " " << v + 1 << " " << other << endl;
        int k;
        cin >> k;
        if (k == 1) {
            seen_c[u] = 1;
            seen_c[v] = 1;
            seen_c[c] = 0;
            U = c;
            goto rep;
        } else if (k == 2) {
            build(u, c, other, ans);
            return;
        } else {
            build(v, c, other, ans);
            return;
        }
    }


    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < m - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int u;
    build(0, 0, n + 1, u);
    int v;
    build(n, n, 1, v);
    cout << "! " << u + 1 << " " << v + 1 << endl;

    return 0;
}
