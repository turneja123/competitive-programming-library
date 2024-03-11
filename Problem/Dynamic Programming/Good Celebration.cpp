//https://www.spoj.com/problems/GOODH/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;
const long long INF = 2e18;

long long b[N], m[N], edge[N];
long long dp[N][N];
vector<int> adj[N];

void calcy(int u, int k, vector<long long> &y, vector<int> &child) {
    for (int i = 0; i <= k; i++) {
        long long l = 0, r = edge[u];
        while (l <= r) {
            long long mid = (l + r) / 2, ct = 0;
            bool flag = true;
            for (int x : child) {
                if (m[x] == 0) {
                    continue;
                }
                int lx = 0, rx = k, cur = k + 1;
                while (lx <= rx) {
                    int j = (lx + rx) / 2;
                    if (dp[x][j] >= mid) {
                        cur = min(cur, j);
                        rx = j - 1;
                    } else {
                        lx = j + 1;
                    }
                }
                ct += cur;
                if (ct > i) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                y[i] = max(y[i], mid);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return;
}

void dfs(int u, int p, int k) {
    if (adj[u].size() == 1 && adj[u][0] == p) {
        for (long long i = 0; i <= k; i++) {
            dp[u][i] = b[u] + m[u] * i;
        }
        return;
    }
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, k);
            child.push_back(v);
        }
    }
    if (m[u] == 0) {
        edge[p] = min(edge[p], b[u]);
        for (long long i = 0; i <= k; i++) {
            dp[u][i] = b[u];
        }
        return;
    }
    vector<long long> y(k + 1, 0);
    calcy(u, k, y, child);

    for (long long i = 0; i <= k; i++) {
        for (int j = 0; i + j <= k; j++) {
            dp[u][i + j] = max(dp[u][i + j], b[u] + m[u] * (i + y[j]));
        }
    }
    return;

}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int u;
        cin >> u >> b[i] >> m[i];
        u--;
        if (u >= 0) {
            adj[i].push_back(u);
            adj[u].push_back(i);

        }
    }
    for (int i = 0; i < n; i++) {
        edge[i] = INF;
        for (int j = 0; j <= k; j++) {
            dp[i][j] = -INF;
        }
    }
    dfs(0, 0, k);
    cout << dp[0][k] << endl;


    return 0;
}
