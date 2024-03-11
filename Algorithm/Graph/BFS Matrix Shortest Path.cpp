#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

char c[N][N];
bool vis[N][N];
int dis[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    pair<int, int> st;
    pair<int, int> gl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            if (c[i][j] == 'S') {
                st = {i, j};
            }
            if (c[i][j] == 'G') {
                gl = {i, j};
            }
        }
    }
    list<pair<int, int>> q;
    q.push_back({st.first, st.second});
    vis[st.first][st.second] = true;
    while (q.size()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop_front();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int zb = abs(dx) + abs(dy);
                if (zb != 2 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m &&
                    c[x + dx][y + dy] != '#' && !vis[x + dx][y + dy]) {

                    dis[x + dx][y + dy] = dis[x][y] + 1;
                    q.push_back({x + dx, y + dy});
                    vis[x + dx][y + dy] = true;
                    if (c[x + dx][y + dy] == 'G') {
                        cout << dis[x + dx][y + dy];
                        return 0;
                    }
                }
            }
        }
    }
    cout << -1;
    return 0;
}
