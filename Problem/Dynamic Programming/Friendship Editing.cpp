//https://usaco.org/index.php?page=viewproblem&cpid=1487
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 17;

int dp[1 << N];
int graph[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u] += 1 << v;
        graph[v] += 1 << u;
    }
    for (int i = 1; i < 1 << n; i++) {
        vector<int> g;
        for (int j = 0; j < n; j++) {
            int c = i & (1 << j);
            if (!c) {
                continue;
            }
            g.push_back(j);
        }
        for (int j = 0; j < g.size(); j++) {
            for (int k = j + 1; k < g.size(); k++) {
                int c = graph[g[j]] & (1 << g[k]);
                if (c) {
                    dp[i]++;
                }
            }
        }
        for (int mask = i; mask > 0; mask = (mask - 1) & i) {
            if (mask == i) {
                continue;
            }
            int comp = i ^ mask;
            int cur = __builtin_popcount(mask) * __builtin_popcount(comp);
            for (int x = mask; x > 0; x &= x - 1) {
                int u = __builtin_ctz(x);
                cur -= __builtin_popcount(graph[u] & comp);
            }
            dp[i] = min(dp[i], dp[mask] + dp[i ^ mask] + cur);
        }
    }
    cout << dp[(1 << n) - 1];
    return 0;
}
