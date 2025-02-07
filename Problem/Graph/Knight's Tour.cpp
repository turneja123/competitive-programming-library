//https://cses.fi/problemset/task/1689/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 8;

vector<pair<int, int>> moves{{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

bool vis[N][N];
int deg[N][N];
int ans[N][N];

bool comp(int x1, int y1, int x2, int y2) {
    return abs(x1 - 3) + abs(y1 - 3) > abs(x2 - 3) + abs(y2 - 3);
}

void calc(int i, int x, int y) {
    vis[x][y] = true;
    ans[x][y] = i;
    int best = N * N;
    pair<int, int> go = make_pair(-1, -1);
    for (auto [dx, dy] : moves) {
        if (x + dx >= 0 && x + dx < 8 && y + dy >= 0 && y + dy < 8 && !vis[x + dx][y + dy]) {
            deg[x + dx][y + dy]--;
            if (deg[x + dx][y + dy] < best) {
                best = deg[x + dx][y + dy];
                go = make_pair(x + dx, y + dy);
            } else if (deg[x + dx][y + dy] == best && comp(x + dx, y + dy, go.first, go.second)) {
                go = make_pair(x + dx, y + dy);
            }
        }
    }
    if (go.first == -1) {
        return;
    }
    calc(i + 1, go.first, go.second);
    return;
}


int main() {
    IOS;
    int x, y;
    cin >> y >> x;
    x--, y--;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (auto [dx, dy] : moves) {
                if (i + dx >= 0 && i + dx < 8 && j + dy >= 0 && j + dy < 8) {
                    deg[i][j]++;
                }
            }
        }
    }
    calc(1, x, y);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
