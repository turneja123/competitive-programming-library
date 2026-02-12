//https://atcoder.jp/contests/arc214/tasks/arc214_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];
int a[N];

void dfs(int u) {
    for (auto [v, wt] : adj[u]) {
        if (a[v] == -1) {
            a[v] = a[u] ^ wt;
            dfs(v);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
        int x = n;
        for (int i = 0; i < n; i++) {
            a[i] = -1;
            x ^= i;
        }
        a[0] = 0;
        dfs(0);
        for (int i = 0; i < n; i++) {
            x ^= a[i];
        }
        if (n % 2 == 0) {
            cout << x << endl;
        } else {
            cout << -1 << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }


    return 0;
}
