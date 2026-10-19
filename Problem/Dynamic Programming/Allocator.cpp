//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 101;

int dp[2][N][N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    vector<tuple<int, int, int, int>> v;
    for (int i = 0; i < n; i ++) {
        int c, r, d, p;
        cin >> c >> r >> d >> p;
        v.push_back({c, r, d, p});
    }
    int X, Y, Z;
    cin >> X >> Y >> Z;

    for (int i = 0; i < n; i++) {
        auto [x, y, z, p] = v[i];
        for (int x_j = 0; x_j <= X; x_j++) {
            for (int y_j = 0; y_j <= Y; y_j++) {
                for (int z_j = 0; z_j <= Z; z_j++) {
                    dp[i & 1][x_j][y_j][z_j] = dp[(i + 1) & 1][x_j][y_j][z_j];
                }
            }
        }
        for (int x_j = 0; x_j + x <= X; x_j++) {
            for (int y_j = 0; y_j + y <= Y; y_j++) {
                for (int z_j = 0; z_j + z <= Z; z_j++) {
                    dp[i & 1][x_j + x][y_j + y][z_j + z] = max(dp[i & 1][x_j + x][y_j + y][z_j + z], dp[(i + 1) & 1][x_j][y_j][z_j] + p);
                }
            }
        }
    }
    int ans = 0;
    for (int x_j = 0; x_j <= X; x_j++) {
        for (int y_j = 0; y_j <= Y; y_j++) {
            for (int z_j = 0; z_j <= Z; z_j++) {
                ans = max(ans, dp[(n + 1) & 1][x_j][y_j][z_j]);
            }
        }
    }
    cout << ans;


    return 0;
}
