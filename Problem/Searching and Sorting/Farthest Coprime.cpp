//https://www.hackerearth.com/problem/algorithm/farthest-coprime-83439671/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int M = 1e3 + 5;

int a[N];

vector<int> goods[M];
vector<int> pos[M];

int main() {
    IOS;
	int n, q, mx = 0;
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		mx = max(mx, a[i]);
		pos[a[i]].push_back(i);
	}
	for (int i = 1; i <= mx; i++) {
		for (int j = 1; j <= mx; j++) {
			if (__gcd(i, j) == 1) {
				goods[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < q; i++) {
		int j;
		cin >> j;
		j--;
		int val = 0, ans = -1, x = a[j];
		for (int p = 0; p < goods[x].size(); p++) {
			int y = goods[x][p];
			if (pos[y].size() == 0) {
				continue;
			}
			if (pos[y][0] < j && j - pos[y][0] >= val) {
				val = j - pos[y][0];
				ans = pos[y][0];
			}
			if (pos[y][pos[y].size() - 1] > j && pos[y][pos[y].size() - 1] - j > val) {
				val = pos[y][pos[y].size() - 1] - j;
				ans = pos[y][pos[y].size() - 1];
			}
		}
		if (ans == -1) {
            ans--;
		}
		cout << ans + 1 << " ";
	}






    return 0;
}
