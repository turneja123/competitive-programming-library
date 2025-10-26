//https://evaluator.hsin.hr/events/coci26_1/tasks/HONI252617kraljica/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int INF = 1e9;

int g_hor[N][N], g_ver[N][N], g_pdg[N][N], g_ndg[N][N];
int dist[N][N];
char a[N][N];

vector<pair<int, int>> tp[10];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    deque<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = s[j];
            dist[i][j] = INF;
            if (a[i][j] == 'S') {
                dist[i][j] = 0;
                q.push_front({i, j});
            }
            if (a[i][j] >= '1' && a[i][j] <= '9') {
                tp[a[i][j] - '0'].push_back({i, j});
            }
        }
    }
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop_front();
        if (a[x][y] >= '1' && a[x][y] <= '9') {
            for (auto [dx, dy] : tp[a[x][y] - '0']) {
                if (dist[dx][dy] > dist[x][y]) {
                    dist[dx][dy] = dist[x][y];
                    q.push_front({dx, dy});
                }
            }
        }
        if (!g_hor[x][y]) {
            for (int add = 0; x - add >= 0; add++) {
                if (a[x - add][y] == '#') {
                    break;
                }
                g_hor[x - add][y] = 1;
                if (dist[x - add][y] > dist[x][y] + 1) {
                    dist[x - add][y] = dist[x][y] + 1;
                    q.push_back({x - add, y});
                }
            }
            for (int add = 0; x + add < n; add++) {
                if (a[x + add][y] == '#') {
                    break;
                }
                g_hor[x + add][y] = 1;
                if (dist[x + add][y] > dist[x][y] + 1) {
                    dist[x + add][y] = dist[x][y] + 1;
                    q.push_back({x + add, y});
                }
            }
        }
        if (!g_ver[x][y]) {
            for (int add = 0; y - add >= 0; add++) {
                if (a[x][y - add] == '#') {
                    break;
                }
                g_ver[x][y - add] = 1;
                if (dist[x][y - add] > dist[x][y] + 1) {
                    dist[x][y - add] = dist[x][y] + 1;
                    q.push_back({x, y - add});
                }
            }
            for (int add = 0; y + add < m; add++) {
                if (a[x][y + add] == '#') {
                    break;
                }
                g_ver[x][y + add] = 1;
                if (dist[x][y + add] > dist[x][y] + 1) {
                    dist[x][y + add] = dist[x][y] + 1;
                    q.push_back({x, y + add});
                }
            }
        }
        if (!g_pdg[x][y]) {
            for (int add = 0; y - add >= 0 && x - add >= 0; add++) {
                if (a[x - add][y - add] == '#') {
                    break;
                }
                g_pdg[x - add][y - add] = 1;
                if (dist[x - add][y - add] > dist[x][y] + 1) {
                    dist[x - add][y - add] = dist[x][y] + 1;
                    q.push_back({x - add, y - add});
                }
            }
            for (int add = 0; y + add < m && x + add < n; add++) {
                if (a[x + add][y + add] == '#') {
                    break;
                }
                g_pdg[x + add][y + add] = 1;
                if (dist[x + add][y + add] > dist[x][y] + 1) {
                    dist[x + add][y + add] = dist[x][y] + 1;
                    q.push_back({x + add, y + add});
                }
            }
        }
        if (!g_ndg[x][y]) {
            for (int add = 0; y + add < m && x - add >= 0; add++) {
                if (a[x - add][y + add] == '#') {
                    break;
                }
                g_ndg[x - add][y + add] = 1;
                if (dist[x - add][y + add] > dist[x][y] + 1) {
                    dist[x - add][y + add] = dist[x][y] + 1;
                    q.push_back({x - add, y + add});
                }
            }
            for (int add = 0; y - add >= 0 && x + add < n; add++) {
                if (a[x + add][y - add] == '#') {
                    break;
                }
                g_ndg[x + add][y - add] = 1;
                if (dist[x + add][y - add] > dist[x][y] + 1) {
                    dist[x + add][y - add] = dist[x][y] + 1;
                    q.push_back({x + add, y - add});
                }
            }
        }
    }
    int ans = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'E' && dist[i][j] != INF) {
                ans = dist[i][j];
            }
        }
    }
    cout << ans;
    return 0;
}
