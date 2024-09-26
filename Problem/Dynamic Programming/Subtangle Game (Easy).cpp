//https://codeforces.com/contest/2005/problem/E1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 305;

int a[N];
int b[N][N];
int mat[N][N][7];
int dp[N][N][15];

vector<pair<int, int>> pos[7];

int pref[N][N][7];
int col[N][N][7];

void preprocess(int n, int m, int k) {
    pref[0][0][k] = mat[0][0][k];
    col[0][0][k] = mat[0][0][k];
    for (int i = 1; i < m; i++) {
        pref[0][i][k] = pref[0][i - 1][k] + mat[0][i][k];
        col[0][i][k] = mat[0][i][k];
    }
    for (int i = 1; i < n; i++) {
        pref[i][0][k] = pref[i - 1][0][k] + mat[i][0][k];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            col[i][j][k] = col[i - 1][j][k] + mat[i][j][k];
            pref[i][j][k] = pref[i][j - 1][k] + col[i][j][k];
        }
    }
}

int get(int y1, int x1, int y2, int x2, int k) {
    int sol = pref[y2][x2][k] - pref[y1 - 1][x2][k] - pref[y2][x1 - 1][k] + pref[y1 - 1][x1 - 1][k];
    return sol;
}

int calc(int n, int m, int r, int c, int ind, int l, int flag) {
    if (dp[r][c][ind] != -1) {
        return dp[r][c][ind];
    }
    int ans = ((flag == 0) ? 1 : 0);
    for (int j = 0; j < pos[a[ind]].size(); j++) {
        int x = pos[a[ind]][j].first, y = pos[a[ind]][j].second;
        if (x < r || y < c) {
            continue;
        }
        x++, y++;
        if (x == n || y == m || ind == l - 1 || get(x, y, n - 1, m - 1, a[ind + 1]) == 0) {
            return dp[r][c][ind] = flag;
        }
    }
    for (int j = 0; j < pos[a[ind]].size(); j++) {
        int x = pos[a[ind]][j].first, y = pos[a[ind]][j].second;
        if (x < r || y < c) {
            continue;
        }
        x++, y++;
        if (flag) {
            ans = max(ans, calc(n, m, x, y, ind + 1, l, 0));
        } else {
            ans = min(ans, calc(n, m, x, y, ind + 1, l, 1));
        }
    }
    return dp[r][c][ind] = ans;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int l, n, m;
        cin >> l >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 15; k++) {
                    dp[i][j][k] = -1;
                    if (k < 7) {
                        mat[i][j][k] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < l; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> b[i][j];
                b[i][j]--;
                pos[b[i][j]].push_back(make_pair(i, j));
                mat[i][j][b[i][j]] = 1;
            }
        }
        for (int k = 0; k < 7; k++) {
            preprocess(n, m, k);
        }
        char ans = ((calc(n, m, 0, 0, 0, l, 1)) ? 'T' : 'N');
        cout << ans << endl;
        for (int k = 0; k < 7; k++) {
            pos[k].clear();
        }

    }
    return 0;
}
