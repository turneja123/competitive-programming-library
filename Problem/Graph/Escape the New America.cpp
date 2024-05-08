//https://www.spoj.com/problems/RDR2_1/
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
int dist[N][N];
int dist2[N][N];
char prv[N][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = n * m + 1;
            dist2[i][j] = n * m + 1;
            if (s[i][j] == 'A') {
                q.push(make_pair(i, j));
                dist[i][j] = 0;
                vis[i][j] = true;
            }
        }
    }
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && s[x + dx][y + dy] != '#' && !vis[x + dx][y + dy]) {
                    vis[x + dx][y + dy] = true;
                    q.push(make_pair(x + dx, y + dy));
                    char c = 'D';
                    if (dx == -1) {
                        c = 'U';
                    } else if (dy == 1) {
                        c = 'R';
                    } else if (dy == -1) {
                        c = 'L';
                    }
                    prv[x + dx][y + dy] = c;
                    dist[x + dx][y + dy] = dist[x][y] + 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vis[i][j] = false;
            if (s[i][j] == 'S') {
                q.push(make_pair(i, j));
                dist2[i][j] = 0;
                vis[i][j] = true;
            }
        }
    }
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && s[x + dx][y + dy] != '#' && !vis[x + dx][y + dy]) {
                    vis[x + dx][y + dy] = true;
                    q.push(make_pair(x + dx, y + dy));
                    dist2[x + dx][y + dy] = dist2[x][y] + 1;
                }
            }
        }
    }
    int ans = n * m + 1; pair<int, int> start = {-1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '#' && (i == 0 || i == n - 1 || j == 0 || j == m - 1) && dist[i][j] < dist2[i][j] && dist[i][j] < ans) {
                ans = dist[i][j];
                start = make_pair(i, j);
            }
        }
    }
    if (start.first == -1) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl << ans << endl;
    string ss = "";
    while (s[start.first][start.second] != 'A') {
        char c = prv[start.first][start.second];
        ss += c;
        if (c == 'U') {
            start.first++;
        } else if (c == 'D') {
            start.first--;
        } else if (c == 'L') {
            start.second++;
        } else {
            start.second--;
        }
    }
    reverse(ss.begin(), ss.end());
    cout << ss;

    return 0;
}
