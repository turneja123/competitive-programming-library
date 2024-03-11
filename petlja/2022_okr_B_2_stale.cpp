#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;
const int N = 105;

int s_x[N];
int s_y[N];
int s_s[N];
int s_d[N];

int s_xy[N][N];
int s_xs[N][N];
int s_xd[N][N];
int s_ys[N][N];
int s_yd[N][N];
int s_sd[N][N];

int s_xys[N][N][N];
int s_xyd[N][N][N];
int s_xsd[N][N][N];
int s_ysd[N][N][N];

int s_xysd[N][N][N][N];

int main() {
    IOS;
    int n, c, ans = 0;
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x += INF, y += INF;
        x %= c, y %= c;
        s_x[x]++, s_y[y]++, s_s[(x + y) % c]++, s_d[(((x - y) % c) + c) % c]++;
        s_xy[x][y]++, s_xs[x][(x + y) % c]++, s_xd[x][(((x - y) % c) + c) % c]++, s_ys[y][(x + y) % c]++, s_yd[y][(((x - y) % c) + c) % c]++, s_sd[(x + y) % c][(((x - y) % c) + c) % c]++;
        s_xys[x][y][(x + y) % c]++, s_xyd[x][y][(((x - y) % c) + c) % c]++, s_xsd[x][(x + y) % c][(((x - y) % c) + c) % c]++, s_ysd[y][(x + y) % c][(((x - y) % c) + c) % c]++;
        s_xysd[x][y][(x + y) % c][(((x - y) % c) + c) % c]++;
    }
    for (int x = 0; x < c; x++) {
        for (int y = 0; y < c; y++) {
            if (s_xy[x][y] > 0) {
                ans = max(ans, s_x[x] + s_y[y] + s_s[(x + y) % c] + s_d[(((x - y) % c) + c) % c] -
                          s_xy[x][y] - s_xs[x][(x + y) % c] - s_xd[x][(((x - y) % c) + c) % c] - s_ys[y][(x + y) % c] - s_yd[y][(((x - y) % c) + c) % c] - s_sd[(x + y) % c][(((x - y) % c) + c) % c] +
                          s_xys[x][y][(x + y) % c] + s_xyd[x][y][(((x - y) % c) + c) % c] + s_xsd[x][(x + y) % c][(((x - y) % c) + c) % c] + s_ysd[y][(x + y) % c][(((x - y) % c) + c) % c] -
                          s_xysd[x][y][(x + y) % c][(((x - y) % c) + c) % c]);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
