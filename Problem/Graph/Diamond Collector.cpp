//https://www.spoj.com/problems/WTPZ2002C/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

bool a[N][N];
int dist[N][N];
bool vis[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> m >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                a[i][j] = false;
                dist[i][j] = N * N;
                vis[i][j] = false;
            }
        }
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int x;
                cin >> x;
                x--;
                a[i][x] = true;
            }
        }
        int ans = N * N;
        deque<pair<int, int>> q;
        q.push_back(make_pair(0, 0));
        dist[0][0] = 0;
        while (q.size()) {
            int x = q.front().first, y = q.front().second;
            q.pop_front();
            if (vis[x][y]) {
                continue;
            }
            vis[x][y] = true;
            if (a[x][y]) {
                if (x == n - 1) {
                    ans = min(ans, dist[x][y]);
                } else {
                    if (dist[x + 1][y] > dist[x][y]) {
                        dist[x + 1][y] = dist[x][y];
                        q.push_front(make_pair(x + 1, y));
                    }
                }
            } else {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dy) == 1 && y + dy >= 0 && y + dy < m && dist[x][y + dy] > 1 + dist[x][y]) {
                        dist[x][y + dy] = 1 + dist[x][y];
                        q.push_back(make_pair(x, y + dy));
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
