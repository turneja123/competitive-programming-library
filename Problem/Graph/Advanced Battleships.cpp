//https://dmoj.ca/problem/abship
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

char a[N][N];
bool vis[N][N];
int head[N][N];

long long sum = 0;
long long cur = 0;
long long ct = 1;
int mp[N * N];

void changeField(int x, int y, bool b) {
    if (a[x][y] != 'X') {
        return;
    }
    if (b == true) {
        mp[head[x][y]]++;
        if (mp[head[x][y]] == 1) {
            cur++;
        }
    } else {
        mp[head[x][y]]--;
        if (mp[head[x][y]] == 0) {
            cur--;
        }
    }
}


int main() {
    IOS;
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    int curhead = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && a[i][j] == 'X') {
                queue<pair<int, int>> q;
                q.push({i, j});
                while (q.size()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    head[x][y] = curhead;
                    vis[x][y] = true;
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (abs(dx) + abs(dy) == 1 && x + dx >= 0 && x + dx < n &&
                            y + dy >= 0 && y + dy < m && !vis[x + dx][y + dy] && a[x + dx][y + dy] == 'X') {
                                q.push({x + dx, y + dy});
                                vis[x + dx][y + dy] = true;
                            }
                        }
                    }
                }
                curhead++;
            }
        }
    }


    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            changeField(i, j, true);
        }
    }
    sum += cur;
    int dir = 0;
    for (int i = 0; i <= n - s; i++) {

        if (dir == 0) {
            for (int j = 0; j < m - s; j++) {

                for (int k = i; k < i + s; k++) {
                    changeField(k, j, false);
                }
                for (int k = i; k < i + s; k++) {
                    changeField(k, j + s, true);
                }
                sum += cur;
                ct++;
            }

            for (int j = m - 1; j > m - 1 - s; j--) {
                changeField(i, j, false);
            }
            if (i < n - s) {
                for (int j = m - 1; j > m - 1 - s; j--) {
                    changeField(i + s, j, true);
                }
                sum += cur;
                ct++;
            }

        } else {
            for (int j = m - 1; j >= s; j--) {

                for (int k = i; k < i + s; k++) {
                    changeField(k, j, false);
                }
                for (int k = i; k < i + s; k++) {
                    changeField(k, j - s, true);
                }
                sum += cur;
                ct++;
            }
            for (int j = 0; j < s; j++) {
                changeField(i, j, false);
            }
            if (i < n - s) {
                for (int j = 0; j < s; j++) {
                    changeField(i + s, j, true);
                }
                sum += cur;
                ct++;
            }

        }
        dir += 1;
        dir %= 2;
    }
    long double sd = sum, sb = ct;
    long double ans = sd / sb;
    cout << fixed << showpoint << setprecision(9) << ans;

}
