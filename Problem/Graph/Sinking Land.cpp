//https://atcoder.jp/contests/abc363/submissions/me
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int K = 1e5 + 5;
const int INF = 1e9;

int a[N][N];
int dist[N][N];
int ct[K];
int pref[K];

int main() {
    IOS;
    int n, m, x;
    cin >> n >> m >> x;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            dist[i][j] = INF;
        }
    }
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            if (i == 0 || j == 0 || i == n + 1 || j == m + 1) {
                pq.push(make_pair(0, make_pair(i, j)));
            }
        }
    }
    while (pq.size()) {
        int d = -pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
        pq.pop();
        if (d != dist[x][y]) {
            continue;
        }
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && x + dx > 0 && x + dx <= n && y + dy > 0 && y + dy <= m) {
                    int cur = max(a[x + dx][y + dy], d);
                    if (cur < dist[x + dx][y + dy]) {
                        dist[x + dx][y + dy] = cur;
                        pq.push(make_pair(-cur, make_pair(x + dx, y + dy)));
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ct[dist[i][j]]++;
        }
    }
    for (int i = 1; i <= x; i++) {
        pref[i] = pref[i - 1] + ct[i];
        cout << n * m - pref[i] << endl;
    }
    return 0;
}

