//https://www.spoj.com/problems/NAKANJ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 8;
const int INF = 1e9;

int dist[N * N][N * N];
vector<pair<int, int>> moves{{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

void precalc(int n, int m) {
    for (int i = 0; i < n * m; i++) {
        for (int j = 0; j < n * m; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cur = i * n + j;
            queue<int> q;
            dist[cur][cur] = 0;
            q.push(cur);

            while (q.size()) {
                int c = q.front();
                q.pop();
                int x = c / n, y = c % m;
                for (int d = 0; d < 8; d++) {
                    int dx = x + moves[d].first, dy = y + moves[d].second;
                    if (dx >= 0 && dx < n && dy >= 0 && dy < m) {
                        int nx = dx * n + dy;
                        if (dist[cur][nx] > dist[cur][c] + 1) {
                            dist[cur][nx] = dist[cur][c] + 1;
                            q.push(nx);
                        }
                    }
                }
            }
        }
    }
}

int get(string &a, int n, int m) {
    return (a[1] - '1') * n + (a[0] - 'a');
}

int main() {
    IOS;
    precalc(8, 8);
    int t;
    cin >> t;
    while (t--) {
        string a, b;
        cin >> a >> b;
        cout << dist[get(a, 8, 8)][get(b, 8, 8)] << endl;
    }
    return 0;
}
