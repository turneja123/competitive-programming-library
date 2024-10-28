//https://atcoder.jp/contests/abc267/tasks/abc267_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

vector<int> adj[N];

int depth[N];
int subtree[N];
int subtree_best[N];
int aux[N];
int aux_best[N];
int dp[N];
int dp_best[N];
int up[K][N];

void dfs_subtree(int u, int p) {
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    subtree_best[u] = u;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            if (subtree[v] + 1 > subtree[u]) {
                subtree[u] = subtree[v] + 1;
                subtree_best[u] = subtree_best[v];
            }
        }
    }
}

int kth(int u, int x) {
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    return u;
}

void dfs(int u, int p) {
    multiset<pair<int, int>> st;
    for (int v : adj[u]) {
        if (v != p) {
            st.insert(make_pair(subtree[v], subtree_best[v]));
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            st.erase(st.find(make_pair(subtree[v], subtree_best[v])));
            dp[v] = dp[u] + 1;
            dp_best[v] = dp_best[u];
            if (st.size() && (*st.rbegin()).first + 2 > dp[v]) {
                dp[v] = (*st.rbegin()).first + 2;
                dp_best[v] = (*st.rbegin()).second;
            }

            st.insert(make_pair(subtree[v], subtree_best[v]));
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_subtree(0, 0);
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, k;
        cin >> u >> k;
        u--;
        if (depth[u] >= k) {
            cout << kth(u, k) + 1 << endl;
            continue;
        }
        if (subtree[u] >= k) {
            cout << kth(subtree_best[u], subtree[u] - k) + 1 << endl;
            continue;
        }
        if (dp[u] >= k) {
            cout << kth(dp_best[u], dp[u] - k) + 1 << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
