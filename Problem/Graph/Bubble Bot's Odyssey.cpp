//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136693
#pragma GCC optimize("Ofast,fast-math")
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

int xa_nx[2 * N][2 * N];
int xb_nx[2 * N][2 * N];

int ya_nx[2 * N][2 * N];
int yb_nx[2 * N][2 * N];

int ans[N][N];
int dp[N][N][N];

vector<pair<int, int>> moves{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};


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
            if (A[i][j] != '-' && A[i][j] != '#') {
                xa[i][j] = i, xb[i][j] = i;
                ya[i][j] = j, yb[i][j] = j;
            }
        }
    }
    for (int t = 0; t < k; t++) {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                xa_nx[i][j] = xa[i][j], ya_nx[i][j] = ya[i][j];
                xb_nx[i][j] = xb[i][j], yb_nx[i][j] = yb[i][j];
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (A[i][j] == '-' || A[i][j] == '#') {
                    continue;
                }
                for (auto [dx, dy] : moves) {
                    if (i + dx >= 0 && i + dx < dim && j + dy >= 0 && j + dy < dim && (A[i + dx][j + dy] == '.' || A[i + dx][j + dy] == 'C')) {
                        xa_nx[i][j] = min(xa_nx[i][j], xa[i + dx][j + dy]);
                        ya_nx[i][j] = min(ya_nx[i][j], ya[i + dx][j + dy]);
                        xb_nx[i][j] = max(xb_nx[i][j], xb[i + dx][j + dy]);
                        yb_nx[i][j] = max(yb_nx[i][j], yb[i + dx][j + dy]);
                    }
                }
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                xa[i][j] = xa_nx[i][j], ya[i][j] = ya_nx[i][j];
                xb[i][j] = xb_nx[i][j], yb[i][j] = yb_nx[i][j];
            }
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
