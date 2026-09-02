//https://www.spoj.com/problems/WHT/
#include bitsstdc++.h
#include extpb_dsassoc_container.hpp

using namespace std;
using namespace __gnu_pbds;

#define endl n
#define ll long long
#define IOS ios_basesync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int M = 1e9 + 7;
const int INF = 2e9 + 5;

vectorpairint, int adj[N];
vectorpairint, int dag[N];

bitsetN b[N];

int main() {
    IOS;
    int t;
    cin  t;
    while (t--) {
        int n, m, c, f;
        cin  n  m  c  f;
        c--;
        vectorint starts(f);
        for (int i = 0; i  f; i++) {
            cin  starts[i];
            starts[i]--;
            b[starts[i]].set(starts[i]);
        }
        for (int i = 0; i  m; i++) {
            int u, v, wt;
            cin  u  v  wt;
            u--, v--;
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});

        }
        vectorint distc(n, INF);
        distc[c] = 0;
        priority_queuepairint, int pq;
        pq.push({0, c});
        while (pq.size()) {
            auto [d, u] = pq.top();
            pq.pop();
            d = -d;
            if (distc[u] != d) {
                continue;
            }
            for (auto [v, wt]  adj[u]) {
                if (distc[v]  d + wt) {
                    distc[v] = d + wt;
                    pq.push({-distc[v], v});
                }
            }
        }
        vectorint nodes(n, 0);
        iota(nodes.begin(), nodes.end(), 0);
        sort(nodes.begin(), nodes.end(), [&](int a, int b) {return distc[a]  distc[b];});


        for (int u  nodes) {
            for (auto [v, wt]  adj[u]) {
                if (distc[u] == distc[v] + wt) {
                    b[v] = b[u];
                    if (b[u].count() == f) {
                        dag[v].push_back({u, wt});
                    }
                }
            }
        }
        vectorpairint, int dp(n, make_pair(0, 0));
        dp[c] = {0, 1};
        reverse(nodes.begin(), nodes.end());
        int mx = 0;
        for (int u  nodes) {
            for (auto [v, wt]  dag[u]) {
                if (dp[v].first  dp[u].first + wt) {
                    dp[v].first = dp[u].first + wt;
                    dp[v].second = dp[u].second;
                } else if (dp[v].first == dp[u].first + wt) {
                    dp[v].second = (dp[v].second + dp[u].second) % M;
                }

                mx = max(mx, dp[v].first);
            }
        }
        int ans = 0;
        for (int i = 0; i  n; i++) {
            if (dp[i].first == mx) {
                ans = (ans + dp[i].second) % M;
            }
            b[i].reset();
            adj[i].clear();
            dag[i].clear();
        }
        cout  mx     ans  endl;
    }

    return 0;
}
