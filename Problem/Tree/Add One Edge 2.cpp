//https://atcoder.jp/contests/abc378/tasks/abc378_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long ans = 0;

vector<int> adj[N];
int deg[N];
int twos[N];


void dfs(int u, int p) {
    int pairs = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (twos[v] > 0) {
                if (deg[u] == 3) {
                    ans += (long long)pairs * twos[v];
                }
                pairs += twos[v];
                if (deg[u] == 2) {
                    ans += twos[v];
                }
            }
            if (deg[u] == 2 && deg[v] == 2) {
                ans--;
            }
        }
    }
    if (deg[u] == 3) {
        twos[u] = pairs;
    } else if (deg[u] == 2) {
        twos[u] = 1;
    } else {
        twos[u] = -1;
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
        deg[v]++;
        deg[u]++;
    }
    for (int i = 0; i < n; i++) {
        twos[i] = -1;
    }
    dfs(0, 0);
    cout << ans;
    return 0;
}
