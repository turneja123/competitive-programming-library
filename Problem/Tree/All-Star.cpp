//https://algotester.com/en/ArchiveProblem/DisplayWithFile/71129#mySolutions
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
vector<tuple<int, int, int>> ans;

void dfs(int u, int p, int r) {
    if (p != r) {
        ans.push_back(make_tuple(r, p, u));
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, r);
        }
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
        deg[u]++, deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int mx = 0, r = -1;
    for (int i = 0; i < n; i++) {
        if (deg[i] > mx) {
            mx = deg[i];
            r = i;
        }
    }
    dfs(r, r, r);
    cout << ans.size() << endl;
    for (auto [x, y, z] : ans) {
        cout << x + 1 << " " << y + 1 << " " << z + 1 << endl;
    }
    return 0;
}
