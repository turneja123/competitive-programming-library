//https://codeforces.com/contest/1316/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

pair<int, int> go[N][N];

int need[N][N];
char ans[N][N];


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            go[i][j] = {x, y};
            if (x >= 0) {
                need[x][y] = 1;
            }
        }
    }
    int ok = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (need[i][j] && !(go[i][j].first == i && go[i][j].second == j)) {
                ok = 0;
            }
            if (need[i][j]) {
                ans[i][j] = 'X';
            } else {
                ans[i][j] = 'Y';
            }
        }
    }


    vector<tuple<int, int, char>> dir{{1, 0, 'U'}, {-1, 0, 'D'}, {0, 1, 'L'}, {0, -1, 'R'}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (need[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                while (q.size()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (auto [dx, dy, c] : dir) {
                        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n && go[x + dx][y + dy] == make_pair(i, j) && ans[x + dx][y + dy] == 'Y') {
                            ans[x + dx][y + dy] = c;
                            q.push({x + dx, y + dy});
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (go[i][j].first < 0 && ans[i][j] == 'Y') {
                int x = -1, y = -1;
                for (auto [dx, dy, c] : dir) {
                    if (i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < n && go[i + dx][j + dy].first < 0) {
                        x = i + dx, y = j + dy;
                        break;
                    }
                }
                if (x == -1) {
                    ok = 0;
                    break;
                }
                if (x == i + 1) {
                    ans[i][j] = 'D';
                    ans[x][y] = 'U';
                } else if (x == i - 1) {
                    ans[i][j] = 'U';
                    ans[x][y] = 'D';
                } else if (y == j + 1) {
                    ans[i][j] = 'R';
                    ans[x][y] = 'L';
                } else {
                    ans[i][j] = 'L';
                    ans[x][y] = 'R';
                }

                queue<pair<int, int>> q;
                q.push({i, j});
                q.push({x, y});
                while (q.size()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (auto [dx, dy, c] : dir) {
                        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < n && go[x + dx][y + dy].first < 0 && ans[x + dx][y + dy] == 'Y') {
                            ans[x + dx][y + dy] = c;
                            q.push({x + dx, y + dy});
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j] == 'Y') {
                ok = 0;
            }
        }
    }

    if (!ok) {
        cout << "INVALID";
        return 0;
    }
    cout << "VALID" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }

    return 0;
}
