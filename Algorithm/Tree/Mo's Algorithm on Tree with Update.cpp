//https://www.codechef.com/problems/DISTNUM3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int freq[N];
int sz;
tuple<int, int, int, int, int> queries[N];
tuple<int, int, int> updates[N];
int ans[N];
gp_hash_table<int, int, custom_hash> pos;
int tour[2 * N];
int vis[N];

bool comp(tuple<int, int, int, int, int> a, tuple<int, int, int, int, int> b) {
    int block1_l = get<0>(a) / sz;
    int block2_l = get<0>(b) / sz;
    if (block1_l != block2_l) {
        return block1_l < block2_l;
    }
    int block1_r = get<1>(a) / sz;
    int block2_r = get<1>(b) / sz;
    if (block1_r != block2_r) {
        return block1_r < block2_r;
    }

    int t1 = get<4>(a);
    int t2 = get<4>(b);
    return t1 < t2;
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

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    sz = cbrt(2 * n * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (pos.find(a[i]) == pos.end()) {
            pos[a[i]] = pos.size();
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
    int t = 0;
    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if (c == 1) {

            int u, v;
            cin >> u >> v;
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            if (l == u) {
                queries[i - t] = make_tuple(tin[u], tin[v], i - t, -1, t);
            } else {
                queries[i - t] = make_tuple(tout[u], tin[v], i - t, l, t);
            }
        } else {
            int j, x;
            cin >> j >> x;
            j--;
            if (pos.find(x) == pos.end()) {
                pos[x] = pos.size();
            }
            x = pos[x];
            updates[t] = make_tuple(x, a[j], j);
            a[j] = x;
            t++;
        }
    }
    q -= t;
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int tq = get<4>(queries[i]);
        while (tq < t) {
            t--;
            int x = get<0>(updates[t]), old = get<1>(updates[t]), j = get<2>(updates[t]);
            if (vis[j] == 1) {
                if ((tin[j] >= l && tin[j] <= r) || (tout[j] >= l && tout[j] <= r)) {
                    freq[x]--;
                    if (freq[x] == 0) {
                        ct--;
                    }
                    freq[old]++;
                    if (freq[old] == 1) {
                        ct++;
                    }
                }
            }
            a[j] = old;
        }
        while (tq > t) {
            int x = get<0>(updates[t]), old = get<1>(updates[t]), j = get<2>(updates[t]);
            if (vis[j] == 1) {
                if ((tin[j] >= l && tin[j] <= r) || (tout[j] >= l && tout[j] <= r)) {
                    freq[old]--;
                    if (freq[old] == 0) {
                        ct--;
                    }
                    freq[x]++;
                    if (freq[x] == 1) {
                        ct++;
                    }
                }
            }
            a[j] = x;
            t++;
        }
        int u;
        while (r < rq) {
            r++;
            u = tour[r];
            vis[u]++;
            if (vis[u] == 1) {
                freq[a[u]]++;
                if (freq[a[u]] == 1) {
                    ct++;
                }
            } else if (vis[u] == 2) {
                freq[a[u]]--;
                if (freq[a[u]] == 0) {
                    ct--;
                }
            }
        }
        while (r > rq) {
            u = tour[r];
            vis[u]--;
            if (vis[u] == 1) {
                freq[a[u]]++;
                if (freq[a[u]] == 1) {
                    ct++;
                }
            } else if (vis[u] == 0) {
                freq[a[u]]--;
                if (freq[a[u]] == 0) {
                    ct--;
                }
            }
            r--;
        }
        while (l < lq) {
            u = tour[l];
            vis[u]--;
            if (vis[u] == 1) {
                freq[a[u]]++;
                if (freq[a[u]] == 1) {
                    ct++;
                }
            } else if (vis[u] == 0) {
                freq[a[u]]--;
                if (freq[a[u]] == 0) {
                    ct--;
                }
            }
            l++;
        }
        while (l > lq) {
            l--;
            u = tour[l];
            vis[u]++;
            if (vis[u] == 1) {
                freq[a[u]]++;
                if (freq[a[u]] == 1) {
                    ct++;
                }
            } else if (vis[u] == 2) {
                freq[a[u]]--;
                if (freq[a[u]] == 0) {
                    ct--;
                }
            }
        }
        int lca = get<3>(queries[i]);
        if (lca == -1) {
            ans[cur] = ct;
        } else {
            freq[a[lca]]++;
            if (freq[a[lca]] == 1) {
                ct++;
            }
            ans[cur] = ct;
            freq[a[lca]]--;
            if (freq[a[lca]] == 0) {
                ct--;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
