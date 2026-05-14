//https://codeforces.com/contest/1350/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int INF = 1e9;

int a[N][N];
int d[N][N];

int main() {
    IOS;
    int n, m, qr;
    cin >> n >> m >> qr;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j] - '0';
            d[i][j] = INF;
        }
    }
    queue<pair<int, int>> q;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int zb = abs(dx) + abs(dy);
                    if (zb == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && a[x][y] == a[x + dx][y + dy]) {
                        d[x][y] = 1;
                    }
                }
            }
            if (d[x][y] == 1) {
                q.push({x, y});
            }
        }
    }
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int zb = abs(dx) + abs(dy);
                if (zb == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && a[x][y] != a[x + dx][y + dy] && d[x + dx][y + dy] > d[x][y] + 1) {
                    d[x + dx][y + dy] = d[x][y] + 1;
                    q.push({x + dx, y + dy});
                }
            }
        }
    }
    for (int i = 0; i < qr; i++) {
        int x, y; ll z;
        cin >> x >> y >> z;
        x--, y--;
        if (d[x][y] == INF || d[x][y] > z) {
            cout << a[x][y] << endl;
        } else {
            int ans = a[x][y];
            if (d[x][y] % 2 == z % 2) {
                ans ^= 1;
            }
            cout << ans << endl;
        }
    }


    return 0;
}
