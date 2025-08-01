//https://www.spoj.com/problems/TWOKINGS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 15;

bool vis[N][N];
char a[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vis[i][j] = 0;
                cin >> a[i][j];
            }
        }
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j]) {
                    continue;
                }
                char c = a[i][j];
                if (c == 'X') {
                    x++;
                } else {
                    y++;
                }

                queue<pair<int, int>> q;
                q.push({i, j});
                vis[i][j] = true;
                while (q.size()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !vis[x + dx][y + dy] && a[x + dx][y + dy] == c) {
                                vis[x + dx][y + dy] = true;
                                q.push({x + dx, y + dy});
                            }
                        }
                    }
                }
            }
        }
        if (x >= y) {
            cout << 'X' << endl;
        } else {
            cout << 'O' << endl;
        }
    }

    return 0;
}
