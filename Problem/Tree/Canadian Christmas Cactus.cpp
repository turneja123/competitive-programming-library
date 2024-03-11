//solution for https://dmoj.ca/problem/wac6p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int deg[N];
bool vis[N];
bool cyc[N];
list<int> adj[N];

void dfs(int v) {
    vis[v] = true;
    vector<int> l;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            parent[*it] = v;
            l.push_back(*it);
            dfs(*it);
        }
    }
    int s = l.size();
    int f = -1;
    for (int i = 0; i < s; i ++) {

        if (f == -1 && !cyc[l[i]]) {
            f = l[i];
        } else if (f != -1 && !cyc[l[i]]) {
            cout << f + 1 << " " << l[i] + 1 << endl;
            f = -1;
        }
    }
    if (f != -1) {
        if (parent[v] != -1 && !cyc[f]) {
            cout << f + 1 << " " << parent[v] + 1 << endl;
            cyc[v] = true;
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }
    int ans = (n - 1) / 2;
    cout << ans << endl;
    parent[0] = -1;
    dfs(0);
    return 0;
}
