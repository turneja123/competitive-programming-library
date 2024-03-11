//solution for https://evaluator.hsin.hr/tasks/HONI202147patkice2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 1e9;

char c[N][N];
int dist[N][N];
bool vis[N][N];
pair<int, int> parent[N][N];

pair<int, int> st;
pair<int, int> fin;
priority_queue<pair<int, pair<int, int>>> pq;
map<char, pair<int, int>> mp;
map<pair<int, int>, char> revmp;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    mp.insert({'>', {0, 1}});
    mp.insert({'<', {0, -1}});
    mp.insert({'^', {-1, 0}});
    mp.insert({'v', {1, 0}});
    mp.insert({'.', {-1, -1}});
    revmp.insert({{0, 1}, '>'});
    revmp.insert({{0, -1}, '<'});
    revmp.insert({{-1, 0}, '^'});
    revmp.insert({{1, 0}, 'v'});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c[i][j];
            dist[i][j] = INF;
            if (c[i][j] == 'o') {
                st = {i, j};
            }
            if (c[i][j] == 'x') {
                fin = {i, j};
            }
        }
    }
    dist[st.first][st.second] = 0;
    pq.push({0, {st.first, st.second}});
    while (pq.size()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();
        vis[x][y] = true;
        pair<int, int> p = mp[c[x][y]];
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (x + dx < 0 || x + dx >= n || y + dy < 0 || y + dy >= m || abs(dx) + abs(dy) != 1) {
                    continue;
                }
                int add = 1;
                if (p == pair<int, int>{dx, dy} || st == pair<int, int>{x, y}) {
                    add = 0;
                }
                if (dist[x + dx][y + dy] > dist[x][y] + add) {
                    dist[x + dx][y + dy] = dist[x][y] + add;
                    parent[x + dx][y + dy] = {x, y};

                    if (pair<int, int>{dx, dy} != fin) {
                        pq.push({-dist[x + dx][y + dy], {x + dx, y + dy}});
                    }
                }
            }
        }
    }
    pair <int, int> p = fin;
    while (p != st) {
        pair<int, int> par = parent[p.first][p.second];
        int dx = p.first - par.first;
        int dy = p.second - par.second;
        if (par != st) {
            c[par.first][par.second] = revmp[pair<int, int>{dx, dy}];
        }
        p = par;
    }
    cout << dist[fin.first][fin.second] << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << c[i][j];
        }
        cout << endl;
    }
    return 0;

}
