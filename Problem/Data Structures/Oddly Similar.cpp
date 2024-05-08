//https://atcoder.jp/contests/abc348/tasks/abc348_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int K = 1005;

bitset<N> b[N];
bitset<N> pos[K];

int a[N][N];

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
	}
	for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            pos[a[i][j]].set(i);
        }
        for (int i = 0; i < n; i++) {
            b[i] ^= pos[a[i][j]];
        }
        for (int i = 0; i < n; i++) {
            pos[a[i][j]].reset(i);
        }
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) {
                ans += b[i][j];
            }
        }
	}
	cout << ans;

	return 0;
}
