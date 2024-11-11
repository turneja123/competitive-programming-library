//https://www.spoj.com/problems/ADASEA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

string s[N];
bool vis[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && s[i][j] == '#') {
                    queue<pair<int, int>> q;
                    q.push(make_pair(i, j));
                    long long sz = 0;
                    while (q.size()) {
                        int x = q.front().first, y = q.front().second;
                        q.pop();
                        if (vis[x][y]) {
                            continue;
                        }
                        sz++;
                        vis[x][y] = true;
                        for (int dx = -1; dx <= 1; dx++) {
                            for (int dy = -1; dy <= 1; dy++) {
                                if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && s[x + dx][y + dy] == '#' && !vis[x + dx][y + dy]) {
                                    q.push(make_pair(x + dx, y + dy));
                                }
                            }
                        }
                    }
                    ans += sz * sz;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                vis[i][j] = false;
            }
        }
        if (ans == 0) {
            cout << 0 << endl;
        } else {
            long long ct = (long long)n * m;
            long long g = __gcd(ans, ct);
            ans /= g, ct /= g;
            if (ct == 1) {
                cout << ans << endl;
            } else {
                cout << ans << " / " << ct << endl;
            }
        }
    }

    return 0;
}
