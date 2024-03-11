#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

pair<int, int> a[N];
list<int> adj[N];
int parent[N];
bool vis[N];

vector<int> ans;
int _time = 0;

void dfs(int v) {
    vis[v] = true;
    _time++;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != parent[v] && !vis[*it]) {
            dfs(*it);
        }
    }
    ans.push_back(v);
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        a[i] = {t, i};
    }
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        parent[v] = u;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[a[i].second]) {
            dfs(a[i].second);
        }
        if (_time > a[i].first) {
            cout << "Pobedila je crna magija";
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }




    return 0;
}
