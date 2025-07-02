//https://www.codechef.com/problems/SHOOT?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long query(int l, int r, int k, vector<vector<long long>> &pref) {
    return pref[k][r] - (l == 0 ? 0 : pref[k][l - 1]);
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
        vector<vector<pair<int, int>>> A(n, vector<pair<int, int>>(m));
        vector<vector<long long>> pref(8, vector<long long>(dim, 0)); //ctxa,ctya,sumxa,sumya,ctxb,ctyb,sumxb,sumyb
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                int x = i + j, y = i - j + m - 1;
                A[i][j] = make_pair(x, y);
                if (a[i][j] == 1 || a[i][j] == 3) {
                    pref[0][x]++;
                    pref[2][x] += x;
                    pref[1][y]++;
                    pref[3][y] += y;
                }
                if (a[i][j] == 2 || a[i][j] == 3) {
                    pref[4][x]++;
                    pref[6][x] += x;
                    pref[5][y]++;
                    pref[7][y] += y;
                }
            }
        }
        for (int k = 0; k < 8; k++) {
            for (int i = 1; i < dim; i++) {
                pref[k][i] += pref[k][i - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                auto [x, y] = A[i][j];
                long long ans = 0;
                ans += query(0, x, 0, pref) * x - query(0, x, 2, pref);
                ans += query(x, dim - 1, 2, pref) - query(x, dim - 1, 0, pref) * x;

                ans += query(0, y, 1, pref) * y - query(0, y, 3, pref);
                ans += query(y, dim - 1, 3, pref) - query(y, dim - 1, 1, pref) * y;

                ans -= query(0, x, 4, pref) * x - query(0, x, 6, pref);
                ans -= query(x, dim - 1, 6, pref) - query(x, dim - 1, 4, pref) * x;

                ans -= query(0, y, 5, pref) * y - query(0, y, 7, pref);
                ans -= query(y, dim - 1, 7, pref) - query(y, dim - 1, 5, pref) * y;

                cout << abs(ans) / 2 << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
