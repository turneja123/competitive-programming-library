//https://atcoder.jp/contests/abc312/tasks/abc312_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int sz[N];
long long pairs[N];

long long ans;

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    int sum = 0;
    for (int v : adj[u]) {
        if (v != p) {
            ans += pairs[v] * (sz[u] - sz[v]); // 2 + 1
            ans += pairs[u] * sz[v]; // 1 + 1 + 1
            pairs[u] += (long long)sum * sz[v];
            sum += sz[v];
        }
    }

    for (int v : adj[u]) {
        if (v != p) {
            pairs[u] += pairs[v];
        }
    }

    return;
}

int main() {
    IOS;
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
    cout << ans;

    return 0;
}
