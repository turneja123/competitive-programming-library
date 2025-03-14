//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136693
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;

char a[N][N];
char A[2 * N][2 * N];

pair<int, int> orig[2 * N][2 * N];
bool vis_nexus[2 * N][2 * N];

bool vis[2 * N][2 * N][N];
bool upd[2 * N][2 * N];


int xa[2 * N][2 * N];
int xb[2 * N][2 * N];

int ya[2 * N][2 * N];
int yb[2 * N][2 * N];
int ans[N][N];
int dp[N][N][N];

vector<pair<int, int>> moves{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

int dfs(int i, int j, int n, int k, int f) {
    auto [x, y] = orig[i][j];
    if (dp[x][y][k] != -1 && dp[x][y][k] != n) {
        return dp[x][y][k];
    }
    dp[x][y][k] = (f == 0 || f == 1 ? i : j);
    if (k == 0) {
        return dp[x][y][k];
    }

    for (auto [du, dv] : moves) {
        if (i + du >= 0 && i + du < n && j + dv >= 0 && j + dv < n && A[i + du][j + dv] == '.') {
            if (f == 0 || f == 2) {
                dp[x][y][k] = min(dp[x][y][k], dfs(i + du, j + dv, n, k - 1, f));
            } else {
                dp[x][y][k] = max(dp[x][y][k], dfs(i + du, j + dv, n, k - 1, f));
            }
        }
    }
    return dp[x][y][k];
}


int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    int dim = n + m - 1;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            A[i][j] = '-';
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j];
            int x = i + j, y = i - j + m - 1;
            A[x][y] = a[i][j];
            orig[x][y] = make_pair(i, j);
        }
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            xa[i][j] = dim, ya[i][j] = dim;
            xb[i][j] = -1, yb[i][j] = -1;
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] == 'C' && !vis_nexus[i][j]) {
                vis_nexus[i][j] == true;
                queue<tuple<int, int, int>> q;
                vector<pair<int, int>> ve;
                q.push(make_tuple(i, j, k));
                int XA = dim, XB = -1, YA = dim, YB = -1;
                while (q.size()) {
                    auto [u, v, t] = q.front();
                    if (!upd[u][v]) {
                        upd[u][v] = true;
                        ve.push_back(make_pair(u, v));
                    }
                    XA = min(XA, u);
                    XB = max(XB, u);
                    YA = min(YA, v);
                    YB = max(YB, v);
                    q.pop();
                    if (t == 0) {
                        continue;
                    }
                    for (auto [du, dv] : moves) {
                        int nw = t - 1;
                        if (A[u + du][v + dv] == 'C' ) {
                            nw = k;
                        }
                        if (u + du >= 0 && u + du < dim && v + dv >= 0 && v + dv < dim && !vis[u + du][v + dv][nw] && (A[u + du][v + dv] == '.' || A[u + du][v + dv] == 'C')) {
                            vis[u + du][v + dv][nw] = true;
                            q.push(make_tuple(u + du, v + dv, nw));
                        }
                    }
                }
                for (auto [u, v] : ve) {
                    for (int t = 0; t <= k; t++) {
                        vis[u][v][t] = false;
                        upd[u][v] = false;
                    }
                    if (A[u][v] == 'C') {
                        vis_nexus[u][v] = true;
                    }
                    xa[u][v] = min(xa[u][v], XA);
                    xb[u][v] = max(xb[u][v], XB);
                    ya[u][v] = min(ya[u][v], YA);
                    yb[u][v] = max(yb[u][v], YB);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t <= k; t++) {
                dp[i][j][t] = dim;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] != '.') {
                continue;
            }
            auto [x, y] = orig[i][j];
            if (dp[x][y][k] == dim) {
                dp[x][y][k] = dfs(i, j, dim, k, 0);
            }
            xa[i][j] = min(xa[i][j], dp[x][y][k]);
        }
    }
    //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t <= k; t++) {
                dp[i][j][t] = -1;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] != '.') {
                continue;
            }
            auto [x, y] = orig[i][j];
            if (dp[x][y][k] == -1) {
                dp[x][y][k] = dfs(i, j, dim, k, 1);
            }
            xb[i][j] = max(xb[i][j], dp[x][y][k]);
        }
    }
    //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t <= k; t++) {
                dp[i][j][t] = dim;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] != '.') {
                continue;
            }
            auto [x, y] = orig[i][j];
            if (dp[x][y][k] == dim) {
                dp[x][y][k] = dfs(i, j, dim, k, 2);
            }
            ya[i][j] = min(ya[i][j], dp[x][y][k]);
        }
    }
    //
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t <= k; t++) {
                dp[i][j][t] = -1;
            }
        }
    }
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] != '.') {
                continue;
            }
            auto [x, y] = orig[i][j];
            if (dp[x][y][k] == -1) {
                dp[x][y][k] = dfs(i, j, dim, k, 3);
            }
            yb[i][j] = max(yb[i][j], dp[x][y][k]);
        }
    }
    //
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (A[i][j] == '-') {
                continue;
            }
            auto [x, y] = orig[i][j];
            if (A[i][j] == '#') {
                ans[x][y] = -1;
                continue;
            }
            ans[x][y] = max({ans[x][y], i - xa[i][j], j - ya[i][j], xb[i][j] - i, yb[i][j] - j});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
