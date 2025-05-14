//https://codeforces.com/contest/2028/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;
const long long M = 998244353;

long long ans[N];
int far[N];
int depth[N];
vector<int> adj[N];

long long modPow(long long a, long long y) {
    long long ans = 1;
    while (y) {
        if (y % 2 == 1) {
            ans = ans * a % M;
        }
        a = a * a % M;
        y /= 2;
    }
    return ans;
}

void dfs(int u, int p) {
    far[u] = INF;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            far[u] = min(far[u], far[v]);
        }
    }
    if (u != 0 && adj[u].size() == 1) {
        far[u] = depth[u];
    }
}

void dfs_calc(int u, int p) {
    if (u == 0) {
        ans[u] = 1;
    } else if (adj[u].size() == 1) {
        ans[u] = 0;
    } else {
        ans[u] = ans[p] * (far[u] - depth[u]) % M * modPow(far[u] - depth[u] + 1, M - 2) % M;
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_calc(v, u);
        }
    }

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        dfs_calc(0, 0);
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
            adj[i].clear();
        }
        cout << endl;
    }
    return 0;
}
