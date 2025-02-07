//https://cses.fi/problemset/task/1684/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> adj[N];
vector<int> rev[N];
stack<int> s;

int a[N];
bool vis[N];
int parent[N];
int deg[N];
int ans[N];
vector<int> comp[N];
set<int> scc[N];

void fillStack(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            fillStack(v);
        }
    }
    s.push(u);
}

void dfs(int u, int j) {
    vis[u] = true;
    parent[u] = j;
    comp[j].push_back(u);
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs(v, j);
        }
    }
}

void add_edge(int a, int b) {
    adj[a].push_back(b);
    rev[b].push_back(a);
}

int main() {
    IOS;
    int n, m;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int a, b; char ca, cb;
        cin >> ca >> a >> cb >> b;
        a--, b--;
        if (ca == '-') {
            a += n;
        }
        if (cb == '-') {
            b += n;
        }
        add_edge((a + n) % (2 * n), b);
        add_edge((b + n) % (2 * n), a);
    }
    for (int i = 0; i < 2 * n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        vis[i] = 0;
    }
    int j = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, j++);
        }
    }
    for (int i = 0; i < n; i++) {
        if (parent[i] == parent[i + n]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    for (int u = 0; u < 2 * n; u++) {
        for (int v : adj[u]) {
            if (parent[u] != parent[v]) {
                auto it = scc[parent[u]].find(parent[v]);
                if (it == scc[parent[u]].end()) {
                    scc[parent[u]].insert(parent[v]);
                    deg[parent[v]]++;
                }
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < j; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> comps;
    while (q.size()) {
        int u = q.front();
        q.pop();
        comps.push_back(u);
        for (int v : scc[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < 2 * n; i++) {
        ans[i] = -1;
    }
    reverse(comps.begin(), comps.end());
    for (int x : comps) {
        int val = -1;
        for (int y : comp[x]) {
            if (ans[y] != -1) {
                val = ans[y];
                break;
            }
        }
        if (val == -1) {
            val = 1;
        }
        for (int y : comp[x]) {
            if (y < n) {
                ans[y] = val;
                ans[y + n] = (val + 1) % 2;
            } else {
                ans[y - n] = (val + 1) % 2;
                ans[y] = val;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!ans[i]) {
            cout << "- ";
        } else {
            cout << "+ ";
        }
    }



    return 0;
}
