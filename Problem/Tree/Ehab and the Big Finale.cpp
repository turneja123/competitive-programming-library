//https://codeforces.com/contest/1174/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int sz[N];
int seen_c[N];
int depth[N];
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
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);

        }
    }
    return;
}

void build(int U, int p, int other, int &ans) {
    dfs_subtree(U, U);
    int c = dfs_centroid(U, U, sz[U]);
    if (p == -1) {
        p = c;
    }
    seen_c[c] = true;

    if (other == 0) {
        ans = U;
        return;
    }
    if (other == -1) {
        cout << "d " << U + 1 << endl;
        cin >> other;
        if (other == 0) {
            ans = U;
            return;
        }
    }
    if (U == c) {
        int v;
        cout << "s " << c + 1 << endl;
        cin >> v;
        v--;
        build(v, c, other - 1, ans);
        return;
    }


    int a = -1;
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs(v, v);
        }
    }
    int k;
    cout << "d " << c + 1 << endl;
    cin >> k;
    if (k == 0) {
        ans = c;
        return;
    }
    if (other - k >= depth[U]) {
        int v;
        cout << "s " << c + 1 << endl;
        cin >> v;
        v--;
        build(v, c, k - 1, ans);
    } else {
        build(U, c, other, ans);
    }

    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int u;
    build(0, 0, -1, u);
    cout << "! " << u + 1 << endl;

    return 0;
}
