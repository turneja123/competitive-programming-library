//https://codeforces.com/contest/2043/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2005;

int a[N][N];
int b[N][N];
int z[N][N];

vector<int> adj[N];

bool cycle;
int color[N];
bool must[N];

void dfs(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v);
        } else if (color[v] == 1) {
            cycle = true;
        }
        if (cycle) {
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> b[i][j];
            }
        }
        string ans = "Yes";
        for (int k = 0; k < 30 && ans == "Yes"; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int ca = a[i][j] & (1 << k), cb = b[i][j] & (1 << k);
                    if (ca && cb) {
                        z[i][j] = 0;
                    } else if (ca && !cb) {
                        z[i][j] = 1;
                    } else if (!ca && cb) {
                        z[i][j] = 2;
                    } else {
                        z[i][j] = 3;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (z[i][j] == 0 || z[i][j] == 2) {
                        adj[i].push_back(j + n);
                    }
                    if (z[i][j] == 1 || z[i][j] == 3) {
                        adj[j + n].push_back(i);
                    }
                    if (z[i][j] == 1) {
                        must[i] = true;
                    }
                    if (z[i][j] == 2) {
                        must[j + n] = true;
                    }
                }
            }
            for (int i = 0; i < n + m; i++) {
                if (color[i] == 0 && must[i]) {
                    dfs(i);
                }
            }
            if (cycle) {
                ans = "No";
            }
            for (int i = 0; i < n + m; i++) {
                adj[i].clear();
                color[i] = 0;
                must[i] = false;
            }
            cycle = false;
        }
        cout << ans << endl;
    }
    return 0;
}
