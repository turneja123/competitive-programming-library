//https://atcoder.jp/contests/abc251/tasks/abc251_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

void dfs(int u, vector<int> &seen) {
    seen[u] = 1;
    for (int v : adj[u]) {
        if (!seen[v]) {
            cout << u + 1 << " " << v + 1 << endl;
            dfs(v, seen);
        }
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> seen(n, 0);
    dfs(0, seen);
    for (int i = 0; i < n; i++) {
        seen[i] = 0;
    }
    queue<int> q;
    q.push(0);
    seen[0] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!seen[v]) {
                cout << u + 1 << " " << v + 1 << endl;
                seen[v] = 1;
                q.push(v);
            }
        }
    }
    return 0;
}
