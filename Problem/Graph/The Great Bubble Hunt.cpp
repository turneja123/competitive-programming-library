//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136692
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e6 + 5;

vector<pair<int, int>> adj[N];

pair<pair<int, int>, int> edges[N];
int depth[N];
bool vis[N];
bool visedge[N];
int parent[N];
int inedge[N];
int cycleid[N];
long long tot[N];
long long sum[N];
int ct[N];

vector<vector<int>> cycles;

void dfs(int u, int p) {
    vis[u] = true;
    for (pair<int, int> p : adj[u]) {
        int e = p.first, v = p.second;
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            parent[v] = u;
            inedge[v] = e;
            visedge[e] = true;
            dfs(v, u);
        } else if (!visedge[e]) {
            visedge[e] = true;
            vector<int> cyc;
            int x = u;
            while (x != v) {
                cycleid[inedge[x]] = cycles.size();
                cyc.push_back(inedge[x]);
                x = parent[x];
            }
            cycleid[e] = cycles.size();
            cyc.push_back(e);
            for (int i = 0; i < cyc.size(); i++) {
                tot[cycles.size()] += edges[cyc[i]].second;
            }
            cycles.push_back(cyc);
        }
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].emplace_back(i, v);
        adj[v].emplace_back(i, u);
        edges[i] = make_pair(make_pair(u, v), wt);
        cycleid[i] = -1;
    }
    dfs(0, 0);
    if (!vis[n - 1]) {
        cout << "Tie";
        return 0;
    }
    int u = n - 1;
    vector<int> e;
    while (u != 0) {
        e.push_back(inedge[u]);
        u = parent[u];
    }
    for (int i = 0; i < e.size(); i++) {
        if (cycleid[e[i]] == -1) {
            cout << "Win";
            return 0;
        }
        ct[cycleid[e[i]]]++;
        sum[cycleid[e[i]]] += edges[e[i]].second;
    }
    long long l = 0, r = 0;
    for (int i = 0; i < cycles.size(); i++) {
        if (ct[i] == 0) {
            continue;
        }
        int m = cycles[i].size();
        if (m % 2 == 1 || ct[i] != m / 2) {
            cout << "Win";
            return 0;
        }
        l += min(sum[i], tot[i] - sum[i]), r += max(sum[i], tot[i] - sum[i]);
    }
    cout << r - l;

    return 0;
}
