//https://cses.fi/problemset/task/3359/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

string s[N];

int dp[N][N];
pair<int, int> go[N][N];
vector<pair<int, int>> point[2 * N];

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < n; j++) {
            point[n - 1 - i + n - 1 - j].push_back(make_pair(i, j));
        }
	}
	int id = 0;
	dp[n - 1][n - 1] = id++;
	for (int k = 1; k < 2 * n; k++) {
        vector<tuple<int, int, int, int>> sorted;
        for (auto [i, j] : point[k]) {
            int cur = 0;
            if (i == n - 1) {
                go[i][j] = make_pair(i, j + 1);
                cur = dp[i][j + 1];
            } else if (j == n - 1) {
                go[i][j] = make_pair(i + 1, j);
                cur = dp[i + 1][j];
            } else if (dp[i + 1][j] < dp[i][j + 1]) {
                go[i][j] = make_pair(i + 1, j);
                cur = dp[i + 1][j];
            } else {
                go[i][j] = make_pair(i, j + 1);
                cur = dp[i][j + 1];
            }
            sorted.push_back(make_tuple(s[i][j] - 'A', cur, i, j));
        }
        sort(sorted.begin(), sorted.end());
        for (auto [_, cur, i, j] : sorted) {
            dp[i][j] = id++;
        }
	}
	int i = 0, j = 0;
	string ans = "";
	while (i != n - 1 || j != n - 1) {
        ans += s[i][j];
        tie(i, j) = go[i][j];
	}
    cout << ans << s[i][j];
	return 0;
}
