//https://www.spoj.com/problems/PCPC12F/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

using ld = long double;
const ld eps = 1e-9;

int Gauss(vector<vector<ld>> a, vector<ld> &ans) {
    int n = (int)a.size(), m = (int)a[0].size() - 1;
    vector<int> pos(m, -1);
    ld det = 1; int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        for (int i = row; i < n; i++) {
            if(fabs(a[i][col]) > fabs(a[mx][col])) {
                mx = i;
            }
        }
        if (fabs(a[mx][col]) < eps) {
            det = 0;
            continue;
        }
        for (int i = col; i <= m; i++) {
            swap(a[row][i], a[mx][i]);
        }
        if (row != mx) {
            det = -det;
        }
        det *= a[row][col];
        pos[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row && fabs(a[i][col]) > eps) {
                ld c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row; ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (pos[i] != -1) {
            ans[i] = a[pos[i]][m] / a[pos[i]][i];
        }
    }
    for (int i = 0; i < n; i++) {
        ld sum = 0;
        for (int j = 0; j < m; j++) {
            sum += ans[j] * a[i][j];
            if (fabs(sum - a[i][m]) > eps) {
                return -1; //no solution
            }
        }
    }
    for (int i = 0; i < m; i++) {
        if (pos[i] == -1) {
            return 2; //infinite solutions
        }
    }
    return 1; //unique solution
}

int go[N];
int go_final[N];

int dfs(int u) {
    if (go[u] == -1) {
        return u;
    }
    if (go_final[u] != -1) {
        return go_final[u];
    }
    return go_final[u] = dfs(go[u]);
}

int main() {
    //IOS;
    cout << fixed;
    cout << setprecision(3);
    int r, c, s, l;
    while (cin >> r >> c>> s >> l) {
        int n = r * c + 1;
        for (int i = 0; i < n; i++) {
            go[i] = -1;
            go_final[i] = -1;
        }
        for (int i = 0; i < s; i++) {
            int u, v;
            cin >> u >> v;
            go[u] = v;
        }
        for (int i = 0; i < l; i++) {
            int u, v;
            cin >> u >> v;
            go[u] = v;
        }
        for (int i = 0; i < n; i++) {
            if (go[i] != -1) {
                dfs(i);
            }
        }
        vector<vector<ld>> v(n, vector<ld>(n + 1, 0));
        v[n - 1][n - 1] = 1.0;
        for (int i = 0; i < n - 1; i++) {
            if (go[i] == -1) {
                v[i][i] += -1.0;
                v[i][n] += -1.0;
                for (int d = 1; d <= 6; d++) {
                    int u = i + d;
                    if (u >= n) {
                        v[i][i] += (ld)1.0/(ld)6.0;
                    } else if (go[u] != -1) {
                        u = go_final[u];
                        v[i][u] += (ld)1.0/(ld)6.0;
                    } else {
                        v[i][u] += (ld)1.0/(ld)6.0;
                    }
                }
            }
        }
        vector<ld> ans(n);
        Gauss(v, ans);
        cout << ans[0] << endl;
    }

    return 0;
}
