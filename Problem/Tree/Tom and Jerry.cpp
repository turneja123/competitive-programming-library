//https://codeforces.com/contest/2245/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int val[N];
int sum[N];
ll ans = 0;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (val[u] == 0) {
                int cur = (val[v] ? 1 : sum[v]);
                ans += (ll)sum[u] * cur;
                sum[u] += cur;
            } else {
                if (val[v]) {
                    ans++;
                } else {
                    ans += sum[v];
                }
            }
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

        for (int i = 0; i < n; i++) {
            val[i] = (int)adj[i].size() % 2;
        }
        ans = 0;
        dfs(0, -1);
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            val[i] = 0;
            sum[i] = 0;
        }
    }

    return 0;
}
