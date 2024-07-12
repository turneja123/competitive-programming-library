//https://www.spoj.com/problems/COT/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int freq[2 * N];
int sz;
tuple<int, int, int, int, int> queries[N];
int ans[N];
int tour[2 * N];
int vis[N];
int block[2 * N];
int ct[N];
int val[N];
pair<int, int> compr[N];

bool comp(tuple<int, int, int, int, int> a, tuple<int, int, int, int, int> b) {
    int block1 = block[get<0>(a)];
    int block2 = block[get<0>(b)];
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

void dfs(int v, int p) {
    tour[timer] = v;
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        int u = *it;
        if (u != p) {
            dfs(u, v);
        }
    }
    tour[timer] = v;
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

int query(int k) {
    int j = 0;
    while (ct[j] < k) {
        k -= ct[j];
        j++;
    }
    for (int i = sz * j; i < sz * (j + 1); i++) {
        k -= freq[i];
        if (k <= 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    sz = sqrt(n);
    for (int i = 0; i < 2 * N; i++) {
        block[i] = i / sz;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr[i] = make_pair(a[i], i);
    }
    sort(compr, compr + n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && compr[i].first > compr[i - 1].first) {
            m++;
        }
        val[m] = a[compr[i].second];
        a[compr[i].second] = m;
    }
    m++;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int l = lca(u, v);
        if (l == u) {
            queries[i] = make_tuple(tin[u], tin[v], i, -1, k);
        } else {
            queries[i] = make_tuple(tout[u], tin[v], i, l, k);
        }
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int k = get<4>(queries[i]);
        int u;
        while (r < rq) {
            r++;
            u = tour[r];
            vis[u]++;
            if (vis[u] == 1) {
                freq[a[u]]++;
                ct[block[a[u]]]++;
            } else if (vis[u] == 2) {
                freq[a[u]]--;
                ct[block[a[u]]]--;
            }
        }
        while (r > rq) {
            u = tour[r];
            vis[u]--;
            if (vis[u] == 1) {
                freq[a[u]]++;
                ct[block[a[u]]]++;
            } else if (vis[u] == 0) {
                freq[a[u]]--;
                ct[block[a[u]]]--;
            }
            r--;
        }
        while (l < lq) {
            u = tour[l];
            vis[u]--;
            if (vis[u] == 1) {
                freq[a[u]]++;
                ct[block[a[u]]]++;
            } else if (vis[u] == 0) {
                freq[a[u]]--;
                ct[block[a[u]]]--;
            }
            l++;
        }
        while (l > lq) {
            l--;
            u = tour[l];
            vis[u]++;
            if (vis[u] == 1) {
                freq[a[u]]++;
                ct[block[a[u]]]++;
            } else if (vis[u] == 2) {
                freq[a[u]]--;
                ct[block[a[u]]]--;
            }
        }
        int t = get<3>(queries[i]);
        if (t == -1) {
            ans[cur] = query(k);
        } else {
            freq[a[t]]++;
            ct[block[a[t]]]++;
            ans[cur] = query(k);

            freq[a[t]]--;
            ct[block[a[t]]]--;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << val[ans[i]] << endl;
    }
    return 0;
}
