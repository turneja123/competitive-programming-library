//https://dmoj.ca/problem/year2018p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 150;
const int sz = 315;

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int val[N];
tuple<int, int, int, int> queries[N];
int ans[N];
map<int, int> pos;
int tour[2 * N];
int vis[N];

int blocks;
multiset<int> block[sz + 200];
multiset<int> diff[sz + 200];

bool seen[N];
int flag[N];

bool comp(tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
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
    for (int u : adj[v]) {
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

void add(int x) {
    int j = x / SQ;
    if (block[j].empty()) {
        block[j].insert(x);
        return;
    }
    auto r = block[j].lower_bound(x);
    if (r != block[j].end() && *r == x) {
        block[j].insert(x);
        diff[j].insert(0);
        return;
    }
    if (r != block[j].begin() && r != block[j].end()) {
        auto l = r;
        l--;
        diff[j].erase(diff[j].find(val[*r] - val[*l]));
    }
    if (r != block[j].end()) {
        diff[j].insert(val[*r] - val[x]);
    }
    if (r != block[j].begin()) {
        auto l = r;
        l--;
        diff[j].insert(val[x] - val[*l]);

    }
    block[j].insert(x);
    return;
}

void del(int x) {
    int j = x / SQ;
    auto r = block[j].lower_bound(x);
    r++;
    if (r != block[j].end()) {
        if (*r == x) {
            diff[j].erase(diff[j].find(0));
            block[j].erase(block[j].find(x));
            return;
        }
        diff[j].erase(diff[j].find(val[*r] - val[x]));
    }
    r--;
    if (r != block[j].begin()) {
        r--;
        diff[j].erase(diff[j].find(val[x] - val[*r]));
        r++;
    }
    r++;
    if (r != block[j].end()) {
        auto l = r;
        l--;
        if (l != block[j].begin()) {
            l--;
            diff[j].insert(val[*r] - val[*l]);
        }
    }
    block[j].erase(block[j].find(x));
    return;
}

int calc() {
    int ans = 2e9, last = -1;
    for (int i = 0; i < blocks; i++) {
        if (diff[i].size()) {
            ans = min(ans, *diff[i].begin());
        }
        if (block[i].size()) {
            if (last != -1) {
                ans = min(ans, val[*block[i].begin()] - val[last]);
            }
            last = *block[i].rbegin();
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    blocks = n / SQ;
    if (n % SQ) {
        blocks++;
    }
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    set<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    for (int x : st) {
        auto it = pos.find(x);
        if (it == pos.end()) {
            val[pos.size()] = x;
            pos[x] = pos.size();
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] = pos[a[i]];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int l = lca(u, v);
        if (l == u) {
            queries[i] = make_tuple(tin[u], tin[v], i, -1);
        } else {
            queries[i] = make_tuple(tout[u], tin[v], i, l);
        }
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int u;
        vector<int> upd;
        while (r < rq) {
            r++;
            u = tour[r];
            vis[u]++;
            if (vis[u] == 1) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]++;
            } else if (vis[u] == 2) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]--;
            }
        }
        while (r > rq) {
            u = tour[r];
            vis[u]--;
            if (vis[u] == 1) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]++;
            } else if (vis[u] == 0) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]--;
            }
            r--;
        }
        while (l < lq) {
            u = tour[l];
            vis[u]--;
            if (vis[u] == 1) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]++;
            } else if (vis[u] == 0) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]--;
            }
            l++;
        }
        while (l > lq) {
            l--;
            u = tour[l];
            vis[u]++;
            if (vis[u] == 1) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]++;
            } else if (vis[u] == 2) {
                if (!seen[u]) {
                    upd.push_back(u);
                }
                seen[u] = 1;
                flag[u]--;
            }
        }
        for (int x : upd) {
            if (flag[x] == 1) {
                add(a[x]);
            } else if (flag[x] == -1) {
                del(a[x]);
            }
            seen[x] = 0;
            flag[x] = 0;
        }
        int t = get<3>(queries[i]);
        if (t == -1) {
            ans[cur] = calc();
        } else {
            add(a[t]);
            ans[cur] = calc();
            del(a[t]);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
