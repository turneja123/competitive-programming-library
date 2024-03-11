//solution for https://cses.fi/problemset/task/1674/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list<int> adj[N];

int sz[N];
bool vis[N];

int dfs(int v, int ct) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        a--;
        adj[a].push_back(i);
        adj[i].push_back(a);
    }
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        cout << sz[i] - 1 << " ";
    }
    return 0;
}
