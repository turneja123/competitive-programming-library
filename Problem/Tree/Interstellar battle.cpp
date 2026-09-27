//https://codeforces.com/contest/1045/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1e5 + 5;

vector<int> adj[N];

int p[N];
int deg[N];
ld a[N];
ld s[N];

void dfs(int u, int pa) {
    for (int v : adj[u]) {
        if (v != pa) {
            p[v] = u;
            s[u] += a[v];
            dfs(v, u);
        }
    }
}

ld calc(int n) {
    ld ans = 1.0;
    for (int i = 0; i < n; i++) {
        ans += a[i] * (ld)(deg[i] - 1);
        if (p[i] != -1) {
            ans -= a[i] * a[p[i]];
        }
    }
    return ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(9);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        p[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    dfs(0, -1);
    ld ans = calc(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u; ld x;
        cin >> u >> x;

        ans -= a[u] * (ld)(deg[u] - 1);
        ans += a[u] * s[u];
        if (p[u] != -1) {
            ans += a[u] * a[p[u]];
            s[p[u]] -= a[u];
        }
        a[u] = x;

        ans += a[u] * (ld)(deg[u] - 1);
        ans -= a[u] * s[u];
        if (p[u] != -1) {
            ans -= a[u] * a[p[u]];
            s[p[u]] += a[u];
        }
        cout << ans << endl;
    }
    return 0;
}
