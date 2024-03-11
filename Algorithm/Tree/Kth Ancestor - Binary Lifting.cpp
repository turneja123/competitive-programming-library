//solution for https://cses.fi/problemset/task/1687
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 2e5 + 5;

list<int> adj[N];
vector<int> depth;
vector<vector<int>> up;
int timer = 0, lg;

void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
}

int kth(int v, int k) {
    while (k > 0) {
        int l = log2(k);
        v = up[v][l];
        k ^= 1 << l;
    }
    return v;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    depth.resize(n);
    for (int i = 1; i < n; i++) {
        int v;
        cin >> v;
        v--;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int v, k;
        cin >> v >> k;
        v--;
        if (depth[v] < k) {
            cout << -1 << endl;
        } else {
            cout << kth(v, k) + 1 << endl;
        }
    }
    return 0;
}
