//https://cses.fi/problemset/task/1194/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1005;
const int INF = 1e9;

vector<pair<int, int>> moves{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
vector<char> dir{'D', 'U', 'R', 'L'};

string s[N];
int dist[N][N];
int dist2[N][N];
pair<int, int> parent[N][N];
char c[N][N];

void bfs(queue<pair<int, int>> &q, int n, int m) {
    while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int dx = x + moves[i].first, dy = y + moves[i].second;
            if (dx >= 0 && dx < n && dy >= 0 && dy < m && s[dx][dy] != '#' && dist2[dx][dy] > dist2[x][y] + 1) {
                dist2[dx][dy] = dist2[x][y] + 1;
                q.push(make_pair(dx, dy));
            }
        }
    }
    return;
}

void print(int x0, int y0, int x1, int y1) {
    cout << "YES" << endl;
    vector<char> ans;
    while (!(x1 == x0 && y1 == y0)) {
        ans.push_back(c[x1][y1]);
        pair<int, int> p = parent[x1][y1];
        x1 = p.first, y1 = p.second;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (char c : ans) {
        cout << c;
    }
    return;
}

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
        cin >> s[i];
	}
	int x0, y0;
	queue<pair<int, int>> sources;
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'A') {
                x0 = i, y0 = j;
            }
            dist[i][j] = INF;
            dist2[i][j] = INF;
            if (s[i][j] == 'M') {
                sources.push(make_pair(i, j));
                dist2[i][j] = 0;
            }
        }
	}
	dist[x0][y0] = 0;
	queue<pair<int, int>> q;
	q.push(make_pair(x0, y0));
	while (q.size()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int dx = x + moves[i].first, dy = y + moves[i].second;
            if (dx >= 0 && dx < n && dy >= 0 && dy < m && s[dx][dy] != '#' && dist[dx][dy] > dist[x][y] + 1) {
                dist[dx][dy] = dist[x][y] + 1;
                parent[dx][dy] = make_pair(x, y);
                c[dx][dy] = dir[i];
                q.push(make_pair(dx, dy));
            }
        }
	}
	bfs(sources, n, m);
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '#' && (i == 0 || i == n - 1 || j == 0 || j == m - 1) && dist[i][j] < dist2[i][j]) {
                print(x0, y0, i, j);
                return 0;
            }
        }
	}
	cout << "NO";

	return 0;
}
