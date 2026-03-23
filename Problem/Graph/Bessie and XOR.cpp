//https://contest.joincpi.org/contest?id=Myb-ebc4AHL67vnWMucwU&tab=problem-BuxjBjrziKzHdK7kxF3Mc
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
int need[N];
int ans[N];
int vis[N];
vector<pair<int, int>> adj[N];

int ok;

void dfs(int u, int p, int ed, int big) {
    vis[u] = 1;
    for (auto [v, e] : adj[u]) {
        if (!vis[v]) {
            dfs(v, u, e, big);
        }
    }
    if (ed == -1) {
        if (need[u] && !big) {
            ok = 0;
        }
    } else if (need[u]) {
        need[p] ^= need[u];
        ans[ed] = need[u];
        need[u] ^= need[u];
    }
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    need[0] = a[0], need[n] = a[n - 1];
    for (int i = 1; i < n; i++) {
        need[i] = a[i] ^ a[i - 1];
    }
    int big = 0;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        if (r == n) {
            big = 1;
        }
        l--;
        adj[l].push_back({r, i});
        adj[r].push_back({l, i});
    }
    ok = 1;
    dfs(n, n, -1, big);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i, -1, 0);
        }
    }
    if (!ok) {
        cout << -1 << endl;
    } else {
        cout << m << endl;
        for (int i = 0; i < m; i++) {
            cout << i + 1<< " " << ans[i] << endl;
        }
    }




    return 0;
}
