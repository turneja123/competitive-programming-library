//https://atcoder.jp/contests/abc387/tasks/abc387_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int INF = 1e9;

int dist[N][N][2];
string s[N];

vector<pair<int, int>> moves{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    int x0, y0, x1, y1;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'S') {
                x0 = i, y0 = j;
            }
            if (s[i][j] == 'G') {
                x1 = i, y1 = j;
            }
            dist[i][j][0] = INF;
            dist[i][j][1] = INF;
        }
    }
    queue<tuple<int, int, int>> q;
    dist[x0][y0][0] = 0;
    dist[x0][y0][1] = 0;
    q.push(make_tuple(x0, y0, 0));
    q.push(make_tuple(x0, y0, 1));
    while (q.size()) {
        auto [x, y, t] = q.front();
        q.pop();
        for (int i = t; i < 4; i += 2) {
            int dx = x + moves[i].first, dy = y + moves[i].second;
            if (dx >= 0 && dx < n && dy >= 0 && dy < m && s[dx][dy] != '#' && dist[dx][dy][(t + 1) % 2] > dist[x][y][t] + 1) {
                dist[dx][dy][(t + 1) % 2] = dist[x][y][t] + 1;
                q.push(make_tuple(dx, dy, (t + 1) % 2));
            }
        }
    }
    int ans = min(dist[x1][y1][0], dist[x1][y1][1]);
    if (ans == INF) {
        cout << -1;
    } else {
        cout << ans;
    }
    return 0;
}
