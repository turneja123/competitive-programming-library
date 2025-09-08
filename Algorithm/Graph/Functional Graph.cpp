//https://cses.fi/problemset/task/1160/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 19;

int up[K][N];
int color[N];
int group[N];
bool cycle[N];
int pos[N];
int entry[N];
int sz[N];
int dist[N];
int parent[N];

void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    int v = up[0][u];
    if (color[v] == 0) {
        dfs(v, u);
    } else if (color[v] == 1) {
        int x = u;
        vector<int> cyc;
        while (x != v) {
            cyc.push_back(x);
            x = parent[x];
        }
        cyc.push_back(v);
        reverse(cyc.begin(), cyc.end());
        for (int i = 0; i < cyc.size(); i++) {
            int x = cyc[i];
            cycle[x] = true;
            pos[x] = i;
            dist[x] = 0;
            sz[x] = cyc.size();
            group[x] = v;
        }
    }
    color[u] = 2;
    if (!cycle[u]) {
        group[u] = group[v];
        if (cycle[v]) {
            dist[u] = 1;
            entry[u] = v;
        } else {
            dist[u] = dist[v] + 1;
            entry[u] = entry[v];
        }
    }
}


int kth(int u, int k) {
    for (int i = K - 1; i >= 0; i--) {
        int c = k & (1 << i);
        if (c) {
            u = up[i][u];
        }
    }
    return u;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        j--;
        up[0][i] = j;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i, i);
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (group[u] != group[v] || (cycle[u] && !cycle[v])) {
            cout << -1 << endl;
            continue;
        }
        int d = 0;
        if (!cycle[u] && !cycle[v]) {
            int k = dist[u] - dist[v];
            if (k < 0) {
                cout << -1 << endl;
                continue;
            }
            int vc = kth(u, k);
            if (vc != v) {
                cout << -1 << endl;
                continue;
            }
            d = k;
        } else {
            int U = u;
            if (!cycle[u]) {
                d += dist[u];
                U = entry[u];
            }
            if (pos[U] <= pos[v]) {
                d += pos[v] - pos[U];
            } else {
                d += sz[U] - pos[U] + pos[v];
            }
        }
        cout << d << endl;
    }
    return 0;
}
