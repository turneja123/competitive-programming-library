//https://atcoder.jp/contests/abc351/tasks/abc351_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1005;

string s[N];
int a[N][N];
bool vis[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '#'){
                a[i][j] = 0;
            } else {
                a[i][j] = 2;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && s[i + dx][j + dy] == '#') {
                            a[i][j] = 1;
                        }
                    }
                }
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && a[i][j] == 2) {
                int ct = 0;
                queue<pair<int, int>> q;
                q.push(make_pair(i, j));
                vis[i][j] = true;
                vector<pair<int, int>> v;
                while (q.size()) {
                    int x = q.front().first, y = q.front().second;
                    q.pop();
                    ct++;
                    if (a[x][y] == 1) {
                        v.push_back(make_pair(x, y));
                        continue;
                    }
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && s[x + dx][y + dy] != '#' && !vis[x + dx][y + dy]) {
                                vis[x + dx][y + dy] = true;
                                q.push(make_pair(x + dx, y + dy));
                            }
                        }
                    }
                }
                ans = max(ans, ct);
                for (int x = 0; x < v.size(); x++) {
                    vis[v[x].first][v[x].second] = false;
                }
            }
        }
    }
    cout << ans;

    return 0;
}
