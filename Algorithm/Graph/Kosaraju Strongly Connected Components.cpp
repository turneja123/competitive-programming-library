#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list <int> adj[N];
list <int> rev[N];
stack <int> s;

bool vis[N];

void fillStack(int v) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            fillStack(*it);
        }
    }
    s.push(v);
}

void dfs(int v) {
    vis[v] = true;
    cout << v << " ";
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
       // a--, b--;
        adj[a].push_back(b);
        rev[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v);
            cout << endl;
        }
    }
    return 0;
}
