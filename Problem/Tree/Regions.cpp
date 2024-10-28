//https://dmoj.ca/problem/ioi09p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 25005;
const int SQ = 200;

int a[N];
int tour[N];
int sz[N];
int ind[N];
int ct[N];
int heavy_ans[SQ + 805][M];

int idx = 0;
int euler = 0;

vector<int> heavy;
vector<int> adj[N];
vector<int> group[M];
vector<int> pos[M];

void dfs(int u, int p) {
    tour[u] = euler++;
    sz[u] = 1;
    ct[a[u]]++;
    for (int j : heavy) {
        heavy_ans[ind[j]][a[u]] += ct[j];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    ct[a[u]]--;
}

int main() {
    //IOS;
    int n, m, q;
    cin >> n >> m >> q;;
    cin >> a[0];
    a[0]--;
    group[a[0]].push_back(0);
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u >> a[i];
        u--, a[i]--;
        group[a[i]].push_back(i);
        adj[u].push_back(i);
        adj[i].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        if (group[i].size() > SQ) {
            heavy.push_back(i);
            ind[i] = idx++;
        }
    }
    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(tour[i]);
    }
    for (int i = 0; i < m; i++) {
        sort(pos[i].begin(), pos[i].end());
    }
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (group[x].size() > SQ) {
            cout << heavy_ans[ind[x]][y] << endl;
            continue;
        }
        int ans = 0;
        for (int j : group[x]) {
            int l = lower_bound(pos[y].begin(), pos[y].end(), tour[j]) - pos[y].begin();
            int r = lower_bound(pos[y].begin(), pos[y].end(), tour[j] + sz[j]) - pos[y].begin();
            ans += r - l;
        }
        cout << ans << endl;
    }
    return 0;
}
