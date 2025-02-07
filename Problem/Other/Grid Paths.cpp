//https://cses.fi/problemset/task/1625/
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int ans = 0;

void calc(int i, int x, int y, string &s, vector<vector<bool>> &vis) {
    if (i == 48) {
        if (x == 7 && y == 1) {
            ans++;
        }
        return;
    }
    if (x == 7 && y == 1) {
        return;
    }
    if ((vis[x][y - 1] && vis[x][y + 1]) && (!vis[x - 1][y] && !vis[x + 1][y])) {
		return;
    }
	if ((vis[x - 1][y] && vis[x + 1][y]) && (!vis[x][y - 1] && !vis[x][y + 1])) {
		return;
	}

    if ((s[i] == 'R' || s[i] == '?') && !vis[x][y + 1]) {
        vis[x][y + 1] = true;
        calc(i + 1, x, y + 1, s, vis);
        vis[x][y + 1] = false;
    }
    if ((s[i] == 'L' || s[i] == '?') && !vis[x][y - 1]) {
        vis[x][y - 1] = true;
        calc(i + 1, x, y - 1, s, vis);
        vis[x][y - 1] = false;
    }
    if ((s[i] == 'D' || s[i] == '?') && !vis[x + 1][y]) {
        vis[x + 1][y] = true;
        calc(i + 1, x + 1, y, s, vis);
        vis[x + 1][y] = false;
    }
    if ((s[i] == 'U' || s[i] == '?') && !vis[x - 1][y]) {
        vis[x - 1][y] = true;
        calc(i + 1, x - 1, y, s, vis);
        vis[x - 1][y] = false;
    }
}


int main() {
    IOS;
    string s;
    cin >> s;
    vector<vector<bool>> vis(9, vector<bool>(9, false));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 0 || j == 8 || i == 0 || i == 8) {
                vis[i][j] = true;
            }
        }
    }
    vis[1][1] = true;
    calc(0, 1, 1, s, vis);
    cout << ans << endl;
    return 0;
}
