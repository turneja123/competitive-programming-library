//https://www.spoj.com/problems/ADAPHONE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int freq[N];
int sz;
tuple<int, int, int, int> queries[N];
int ans[N];
int tour[2 * N];
int vis[N];

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

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    sz = sqrt(2 * n);
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
    int ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int u;
        while (r < rq) {
            r++;
            u = tour[r];
            vis[u]++;
            if (vis[u] == 1) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct++;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct++;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct--;
                    }

                }
            } else if (vis[u] == 2) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct--;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct--;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct++;
                    }

                }
            }
        }
        while (r > rq) {
            u = tour[r];
            vis[u]--;
            if (vis[u] == 1) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct++;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct++;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct--;
                    }

                }
            } else if (vis[u] == 0) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct--;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct--;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct++;
                    }

                }
            }
            r--;
        }
        while (l < lq) {
            u = tour[l];
            vis[u]--;
            if (vis[u] == 1) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct++;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct++;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct--;
                    }

                }
            } else if (vis[u] == 0) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct--;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct--;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct++;
                    }

                }
            }
            l++;
        }
        while (l > lq) {
            l--;
            u = tour[l];
            vis[u]++;
            if (vis[u] == 1) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct++;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct++;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct--;
                    }

                }
            } else if (vis[u] == 2) {
                if (u == 0) {
                    if (vis[1] != 1) {
                        ct--;
                    }
                } else {
                    if (vis[u - 1] != 1 && vis[u + 1] != 1) {
                        ct--;
                    } else if (vis[u - 1] == 1 && vis[u + 1] == 1) {
                        ct++;
                    }

                }
            }
        }
        int t = get<3>(queries[i]);
        if (t == -1) {
            ans[cur] = ct;
        } else {
            if (t == 0) {
                if (vis[1] != 1) {
                    ct++;
                }
            } else {
                if (vis[t - 1] != 1 && vis[t + 1] != 1) {
                    ct++;
                } else if (vis[t - 1] == 1 && vis[t + 1] == 1) {
                    ct--;
                }

            }
            ans[cur] = ct;
            if (t == 0) {
                if (vis[1] != 1) {
                    ct--;
                }
            } else {
                if (vis[t - 1] != 1 && vis[t + 1] != 1) {
                    ct--;
                } else if (vis[t - 1] == 1 && vis[t + 1] == 1) {
                    ct++;
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
