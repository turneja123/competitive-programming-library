//https://atcoder.jp/contests/abc477/tasks/abc477_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;
const int SQ = 440;

int f[N];
int c[N];

int up[K][N];
vector<int> ord;
vector<int> adj[N];
int tin[N];
int tout[N];
int depth[N];
int ans[N];
int freq[N];
int freq_col[N];

int ct[N];
int ct_blk[N];


struct Query {
    int l;
    int r;
    int lca;
    int i;
    int L;
    int R;
};

void dfs(int u, int p) {
    tin[u] = ord.size();
    ord.push_back(u);

    up[0][u] = p;
    for (int i = 1; i < K; i++) {
        int v = up[i - 1][u];
        up[i][u] = up[i - 1][v];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    tout[u] = ord.size();
    ord.push_back(u);
}


int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    int d = depth[v] - depth[u];
    for (int i = K - 1; i >= 0; i--) {
        int c = d & (1 << i);
        if (c) {
            v = up[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = K - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int L = lca(u, v);
        if (u == L) {
            queries.push_back({tin[u], tin[v], -1, i, l, r});
        } else {
            queries.push_back({tout[u], tin[v], L, i, l, r});
        }
    }
    sort(queries.begin(), queries.end(), [&](Query &a, Query &b) {
        if (a.l / 630 != b.l / 630) {
            return a.l / 630 < b.l / 630;
        }
        return a.r < b.r;
    });
    auto add = [&](int u, int x) -> void {
        freq[u] += x;
        if (freq[u] == 1) {
            int s = freq_col[c[u]];
            ct[s]--;
            ct_blk[s / SQ]--;
            freq_col[c[u]]++;
            s = freq_col[c[u]];
            ct[s]++;
            ct_blk[s / SQ]++;
        }
        if (freq[u] == 0 || freq[u] == 2) {
            int s = freq_col[c[u]];
            ct[s]--;
            ct_blk[s / SQ]--;
            freq_col[c[u]]--;
            s = freq_col[c[u]];
            ct[s]++;
            ct_blk[s / SQ]++;
        }
    };
    auto get_ans = [&](int l, int r) -> int {
        int ans = 0;
        int l_blk = l / SQ, r_blk = r / SQ;
        if (l_blk == r_blk) {
            for (int i = l; i <= r; i++) {
                ans += ct[i];
            }
            return ans;
        }
        for (int i = l; i < (l_blk + 1) * SQ; i++) {
            ans += ct[i];
        }
        for (int i = l_blk + 1; i < r_blk; i++) {
            ans += ct_blk[i];
        }
        for (int i = r_blk * SQ; i <= r; i++) {
            ans += ct[i];
        }
        return ans;
    };


    int l = 0, r = -1;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, x, ind, L, R] = queries[i];
        while (r < rq) {
            r++;
            add(ord[r], 1);
        }
        while (l > lq) {
            l--;
            add(ord[l], 1);
        }
        while (l < lq) {
            add(ord[l], -1);
            l++;
        }
        while (r > rq) {
            add(ord[r], -1);
            r--;
        }
        if (x != -1) {
            add(x, 1);
            ans[ind] = get_ans(L, R);
            add(x, -1);
        } else {
            ans[ind] = get_ans(L, R);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
