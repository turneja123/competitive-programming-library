//https://atcoder.jp/contests/abc345/tasks/abc345_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

string ans = "No";
vector<pair<int, int>> tiles;

void f(int n, vector<bool> &used, vector<vector<bool>> &vis, int ct, int h, int w, int t) {
    if (ans == "Yes" || used[t]) {
        return;
    }
    used[t] = true;
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            k++;
        }
    }
    int s = 0;
    if (k > 5) {
        s = max(0, min(h, w) / 2 - 2);
    }
    int x = tiles[t].first, y = tiles[t].second;
    for (int is = s; is + x <= h; is++) {
        for (int js = s; js + y <= w; js++) {
            if (is + x > h || js + y > w) {
                    continue;
                }
                if (is > 0 && !vis[is - 1][js]) {
                    break;
                }
                if (js > 0 && !vis[is][js - 1]) {
                    break;
                }
                if (is > 0 && js > 0 && !vis[is - 1][js - 1]) {
                    break;
                }
                int cur = ct;
                bool flag = true;
                vector<pair<int, int>> restore;
                for (int i = is; i < is + x && flag; i++) {
                    for (int j = js; j < js + y && flag; j++) {
                        if (vis[i][j]) {
                            flag = false;
                            break;
                        }
                        vis[i][j] = true;
                        cur++;
                        restore.push_back(make_pair(i, j));
                    }
                }
            if (flag) {
                if (cur == h * w) {
                    ans = "Yes";
                    return;
                }
                for (int i = 0; i < n; i++) {
                    f(n, used, vis, cur, h, w, i);
                }
            }
            for (int i = 0; i < restore.size(); i++) {
                int p = restore[i].first, q = restore[i].second;
                vis[p][q] = false;
            }
        }
    }
    x = tiles[t].second; y = tiles[t].first;
    for (int is = s; is + x <= h; is++) {
        for (int js = s; js + y <= w; js++) {
            if (is > 0 && !vis[is - 1][js]) {
                break;
            }
            if (js > 0 && !vis[is][js - 1]) {
                break;
            }
            if (is > 0 && js > 0 && !vis[is - 1][js - 1]) {
                break;
            }
            int cur = ct;
            bool flag = true;
            vector<pair<int, int>> restore;
            for (int i = is; i < is + x && flag; i++) {
                for (int j = js; j < js + y && flag; j++) {
                    if (vis[i][j]) {
                        flag = false;
                        break;
                    }
                    vis[i][j] = true;
                    cur++;
                    restore.push_back(make_pair(i, j));
                }
            }
            if (flag) {
                if (cur == h * w) {
                    ans = "Yes";
                    break;
                }
                for (int i = 0; i < n; i++) {
                    f(n, used, vis, cur, h, w, i);
                }
            }
            for (int i = 0; i < restore.size(); i++) {
                int p = restore[i].first, q = restore[i].second;
                vis[p][q] = false;
            }
        }
    }
    used[t] = false;
}



int main() {
    IOS;
    int n, h, w;
    cin >> n >> h >> w;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        tiles.push_back(make_pair(x, y));

    }
    vector<vector<bool>> vis(h, vector<bool>(w, false));
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        f(n, used, vis, 0, h, w, i);
    }
    cout << ans;

    return 0;
}
