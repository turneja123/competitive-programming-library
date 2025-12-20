//https://qoj.ac/contest/2511/problem/14110
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int MAX = 1e6;

int a[N][N];
int seen[N][N];
int done[N];
vector<pair<int, int>> go[MAX + 1];

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            go[a[i][j]].push_back({i, j});
        }
	}
	int ans = 0;
	vector<pair<int, int>> ord;
	for (int i = MAX; i > 0; i--) {
        for (int j = 0; j < go[i].size(); j++) {
            auto [x, y] = go[i][j];
            if (seen[x][y] || done[x] || done[y]) {
                continue;
            }
            if (x > y) {
                swap(x, y);
            }
            ans += a[x][y];
            done[y] = 1;
            seen[x][y] = 1;
            seen[y][x] = 1;
            ord.push_back({x, y});
            for (int k = 0; k < n; k++) {
                if (k == x || k == y) {
                    continue;
                }
                a[x][k] = max(a[x][k], a[y][k]);
                a[k][x] = max(a[k][x], a[y][k]);
                go[a[x][k]].push_back({x, k});
            }
        }
	}
	cout << ans << endl;
	for (auto [x, y] : ord) {
        cout << x + 1 << " " << y + 1 << endl;
	}
	return 0;
}
