//https://codeforces.com/contest/1702/problem/G2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int depth[N];

void dfs(int v, int p) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
    }
    tout[v] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

int kth(int v, int k) {
    while (k > 0) {
        int l = log2(k);
        v = up[v][l];
        k ^= 1 << l;
    }
    return v;
}

int main() {
    IOS;
    int n;
    cin >> n;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        v--; u--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<pair<int, int>> v;
        int anc = -1;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            u--;
            v.push_back(make_pair(depth[u], u));
            anc = ((anc == -1) ? u : lca(anc, u));
        }
        sort(v.begin(), v.end(), greater<pair<int, int>>());
        string can = "YES";
        pair<int, int> l = v[0], r = make_pair(-1, -1);
        for (int j = 0; j < v.size() - 1; j++) {
            int d = l.first - v[j + 1].first;
            int u = kth(l.second, d);
            if (u != v[j + 1].second) {
                if (r.first == -1) {
                    r = v[j + 1];
                } else {
                    d = r.first - v[j + 1].first;
                    u = kth(r.second, d);
                    if (u != v[j + 1].second) {
                        can = "NO";
                    } else {
                        r = v[j + 1];
                    }
                }
            } else {
                l = v[j + 1];
            }
            if (r.second != -1 && lca(l.second, r.second) != anc) {
                can = "NO";
            }
        }
        cout << can << endl;
    }

    return 0;
}
