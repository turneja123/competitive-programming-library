//https://atcoder.jp/contests/arc177/tasks/arc177_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;

string s[N];
int dp[N][N][2];
bool vis[N][N][2];
vector<char> c{'R', 'B'};

void dijkstra(int x, int y, int k, int n) {
    dp[x][y][k] = 0;
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push(make_pair(0, make_pair(x, y)));
    while (pq.size()) {
        int i = pq.top().second.first, j = pq.top().second.second;
        pq.pop();
        if (vis[i][j][k]) {
            continue;
        }
        vis[i][j][k] = true;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < n) {
                    int d = dp[i][j][k] + (s[i + dx][j + dy] != c[k]);
                    if (dp[i + dx][j + dy][k] > d && !vis[i + dx][j + dy][k]) {
                        dp[i + dx][j + dy][k] = d;
                        pq.push(make_pair(-d, make_pair(i + dx, j + dy)));
                    }
                }
            }
        }
    }
    return;
}

int main() {
	IOS;
	int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j][0] = N * N;
            dp[i][j][1] = N * N;
        }
    }
    dijkstra(0, 0, 0, n);
    dijkstra(0, n - 1, 1, n);
    cout << dp[n - 1][n - 1][0] + dp[n - 1][0][1];
	return 0;
}
