//https://www.codechef.com/problems/SHOOT?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int calc(int f, int i, int j, int a) {
    if (a <= 0) {
        return 0;
    }
    int player = 0;
    if (f >= 4) {
        player = 1;
    }
    if (player == 0 && a == 1) {
        return 0;
    }
    if (player == 1 && a == 2) {
        return 0;
    }
    if (f == 0 || f == 1 || f == 4 || f == 5) {
        return 1;
    }
    if (f == 2 || f == 6) {
        return j;
    }
    return i;
}

void preprocess(int n, int m, vector<vector<int>> &a, vector<vector<long long>> &pref, int f) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int add = calc(f, i, j, a[i][j]);
            pref[i][j] = add + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

long long query(int x1, int y1, int x2, int y2, vector<vector<long long>> &pref) {
    if (y1 > y2 || x1 > x2) {
        return 0;
    }
    int ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {

        int n, m;
        cin >> n >> m;
        int dim = n + m - 1;
        vector<vector<int>> a(n, vector<int>(m));
        vector<vector<int>> A(dim, vector<int>(dim));
        vector<vector<pair<int, int>>> orig(dim, vector<pair<int, int>>(dim));
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                A[i][j] = -1;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                int x = i + j, y = i - j + m - 1;
                A[x][y] = a[i][j];
                orig[x][y] = make_pair(i, j);
            }
        }
        vector<vector<long long>> pref[8]; //ctxa,ctya,sumxa,sumya,ctxb,ctyb,sumxb,sumyb
        for (int k = 0; k < 8; k++) {
            pref[k].resize(dim, vector<long long>(dim, 0));
            preprocess(dim, dim, A, pref[k], k);
        }
        vector<vector<long long>> ansa(n, vector<long long>(m, 0));
        vector<vector<long long>> ansb(n, vector<long long>(m, 0));
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (A[i][j] == -1) {
                    continue;
                }
                auto [x, y] = orig[i][j];
                ansa[x][y] += (long long)j * query(0, 0, dim - 1, j, pref[0]) - query(0, 0, dim - 1, j, pref[2]);
                ansa[x][y] += (long long)i * query(0, 0, i, dim - 1, pref[1]) - query(0, 0, i, dim - 1, pref[3]);

                ansa[x][y] += query(0, j + 1, dim - 1, dim - 1, pref[2]) - (long long)j * query(0, j + 1, dim - 1, dim - 1, pref[0]);
                ansa[x][y] += query(i + 1, 0, dim - 1, dim - 1, pref[3]) - (long long)i * query(i + 1, 0, dim - 1, dim - 1, pref[1]);

                ansb[x][y] += (long long)j * query(0, 0, dim - 1, j, pref[4]) - query(0, 0, dim - 1, j, pref[6]);
                ansb[x][y] += (long long)i * query(0, 0, i, dim - 1, pref[5]) - query(0, 0, i, dim - 1, pref[7]);

                ansb[x][y] += query(0, j + 1, dim - 1, dim - 1, pref[6]) - (long long)j * query(0, j + 1, dim - 1, dim - 1, pref[4]);
                ansb[x][y] += query(i + 1, 0, dim - 1, dim - 1, pref[7]) - (long long)i * query(i + 1, 0, dim - 1, dim - 1, pref[5]);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << abs(ansa[i][j] - ansb[i][j]) / 2 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
