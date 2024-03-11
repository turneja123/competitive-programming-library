//solution for https://cses.fi/problemset/task/1137
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list <int> adj[N];

int sz[N];
int tour[N];
int vals[N];
ll a[N];
ll seg[2 * N];
bool vis[N];

int euler = 0;

int dfs(int v, int ct) {
    tour[v] = euler++;
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;
}

void build(int n) {
    for (int i = 0; i < n; i++) {
        seg[i + n] = a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
}

ll rsq(int l, int r, int n) {
    l += n;
    r += n;
    ll sum = 0;
    while (l < r) {
        if (l % 2 == 1) {
            sum += seg[l++];
        }
        if (r % 2 == 1) {
            sum += seg[--r];
        }
        l /= 2;
        r /= 2;
    }
    return sum;
}

void update(int pos, int val, int n) {
    pos += n;
    seg[pos] = val;
    while (pos > 1) {
        pos /= 2;
        seg[pos] = seg[pos * 2] + seg[pos * 2 + 1];
    }
}
int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        a[tour[i]] = vals[i];
    }
    build(n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll s, x;
            cin >> s >> x;
            s--;
            update(tour[s], x, n);
        }
        else {
            int s;
            cin >> s;
            s--;
            ll ans = rsq(tour[s], tour[s] + sz[s], n);
            cout << ans << endl;
        }
    }
    return 0;
}
