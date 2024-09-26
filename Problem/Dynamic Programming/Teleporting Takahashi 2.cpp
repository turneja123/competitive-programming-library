//https://atcoder.jp/contests/abc372/tasks/abc372_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

vector<int> adj[N];
vector<int> x;
long long dp[N];

int main(){
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        adj[i].push_back(i - 1);
    }
    adj[0].push_back(n - 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (adj[i].size() > 1) {
            x.push_back(i);
        }
    }
    dp[0] = 1;
    for (int j = 1; j <= k; j++) {
        vector<pair<int, int>> upd;
        for (int v : x) {
            int posv = (v - j % n + n) % n;
            long long dpv = 0;
            for (int u : adj[v]) {
                int posu = (u - (j - 1) % n + n) % n;
                dpv = (dpv + dp[posu]) % M;
            }
            upd.push_back(make_pair(dpv, posv));
        }
        for (int i = 0; i < upd.size(); i++) {
            dp[upd[i].second] = upd[i].first;
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i];
    }
    cout << ans % M;

    return 0;
}
