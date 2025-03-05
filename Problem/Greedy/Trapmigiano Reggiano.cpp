//https://codeforces.com/contest/2071/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> adj[N];
vector<int> ans;

void dfs(int u, int p) {
    ans.push_back(u);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, st, en;
        cin >> n >> st >> en;
        st--, en--;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(en, en);
        for (int i = n - 1; i >= 0; i--) {
            cout << ans[i] + 1 << " ";
            adj[i].clear();
        }
        ans.clear();
        cout << endl;
    }

    return 0;
}
