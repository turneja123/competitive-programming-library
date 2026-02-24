//https://ocpc2026w.eolymp.space/en/compete/rofq4l68mt2dp1esn9ncjjllcg/problem/11
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int p[N];
int parent[N];
int timer_[N];
int child_cnt[N];

ll w[N];
ll leaf_sub[N];
ll is_leaf[N];

ll ct[N][2];

struct Item {
    int u;
    ll x;
    ll y;
    int timer;
};

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    parent[b] = a;
    ct[a][0] += ct[b][0];
    ct[a][1] += ct[b][1];
}

ll solve_min(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        timer_[i] = 0;
        ct[i][0] = w[i];
        ct[i][1] = is_leaf[i];
    }

    auto comp = [&](Item a, Item b) {
        return (__int128)a.x * b.y > b.x * a.y;
    };

    priority_queue<Item, vector<Item>, decltype(comp)> pq(comp);

    for (int i = 1; i < n; i++) {
        if (ct[i][1] > 0) {
            pq.push({i, ct[i][0], ct[i][1], 0});
        }
    }
    ll ans = 0;
    int t = 1;

    while (pq.size()) {
        auto i = pq.top();
        pq.pop();

        if (dsu_find(i.u) != i.u || timer_[i.u] != i.timer) {
            continue;
        }

        int x = i.u;
        int y = dsu_find(p[x]);

        ans += ct[x][0] * ct[y][1];

        timer_[y] = t;
        dsu_unite(y, x);

        if (y != 0 && ct[y][1] > 0) {
            pq.push({y, ct[y][0], ct[y][1], t});
        }
        t++;
    }

    return ans;
}

ll solve_max(int n, vector<int>& ord) {
    vector<ll> dp(n, 0);
    vector<ll> paths;
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (child_cnt[u] == 0) {
            dp[u] = w[u];
        } else {
            ll max_child_dp = -1;
            int heavy_child = -1;
            for (int v : adj[u]) {
                if (v == p[u]) continue;
                if (dp[v] > max_child_dp) {
                    max_child_dp = dp[v];
                    heavy_child = v;
                }
            }

            dp[u] = w[u] + max_child_dp;
            for (int v : adj[u]) {
                if (v == p[u]) continue;
                if (v != heavy_child) {
                    paths.push_back(dp[v]);
                }
            }
        }
    }
    paths.push_back(dp[0]);

    sort(paths.rbegin(), paths.rend());
    ll K = paths.size();
    ll max_cost = 0;

    for (int i = 0; i < K; i++) {
        max_cost += paths[i] * (K - i);
    }

    return max_cost;
}

int main() {
    IOS;
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll s = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        s += w[i];
    }

    vector<int> ord{0};
    p[0] = -1;

    for (int i = 0; i < ord.size(); i++) {
        int u = ord[i];
        for (int v : adj[u]) {
            if (v == p[u]) {
                continue;
            }
            p[v] = u;
            child_cnt[u]++;
            ord.push_back(v);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        if (child_cnt[u] == 0) {
            leaf_sub[u] = 1;
            is_leaf[u] = 1;
        }
        if (u != 0) {
            leaf_sub[p[u]] += leaf_sub[u];
        }
    }
    ll base = leaf_sub[0] * s;

    cout << base - solve_min(n) << " " << solve_max(n, ord) << endl;
    return 0;
}
