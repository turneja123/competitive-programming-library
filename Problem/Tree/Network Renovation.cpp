//https://cses.fi/problemset/task/1704/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int deg[N];

vector<int> adj[N];
vector<int> leaf;

void dfs(int u, int p) {
    int l = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            l = 0;
        }
    }
    if (l) {
        leaf.push_back(u);
    }
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
        deg[u]++;
        deg[v]++;
    }
    int root = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] != 1) {
            root = i;
            break;
        }
    }
    dfs(root, root);
    int m = leaf.size();
    cout << (m + 1) / 2 << endl;
    for (int i = 0; i < (m + 1) / 2; i++) {
        cout << leaf[i] + 1 << " " << leaf[(i + (m + 1) / 2) % m] + 1 << endl;
    }
    return 0;
}
