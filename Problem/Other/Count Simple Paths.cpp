//https://atcoder.jp/contests/abc378/tasks/abc378_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 11;

string s[N];
bool vis[N][N];

int ans = 0;
int n, m, k;

vector<pair<int, int>> moves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int x, int y, int cur) {
    if (cur == k + 1) {
        ans++;
        return;
    }
    for (pair<int, int> p : moves) {
        int dx = p.first, dy = p.second;
        if (x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m && !vis[x + dx][y + dy] && s[x + dx][y + dy] == '.') {
            vis[x + dx][y + dy] = true;
            dfs(x + dx, y + dy, cur + 1);
            vis[x + dx][y + dy] = false;
        }
    }
    return;
}


int main() {
    IOS;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '.') {
                vis[i][j] = true;
                dfs(i, j, 1);
                vis[i][j] = false;
            }
        }
    }
    cout << ans;

    return 0;
}
