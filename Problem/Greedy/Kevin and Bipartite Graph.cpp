//https://codeforces.com/contest/2048/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

vector<int> ans[N];

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, m;
        cin >> n >> m;
        if (2 * n * n - n < n * m) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            for (int i = 0; i < 2 * n; i++) {
                ans[i].clear();
                ans[i].resize(m);
            }
            int i = 0;
            for (int j = 1; j <= min(m, n - 1); j++, i++) {
                for (int c = 1; c <= n; ++c) {
                    ans[c - 1][i] = c;
                    ans[n + ((c + j - 1) % n)][i] = c;
                }
            }

            if (i < m) {
                for (int c = 1; c <= n; c++) {
                    ans[c - 1][i] = c;
                    ans[n + c - 1][i] = c;
                }
                i++;
            }

            for (int k = 1; i < m; i++, k++) {
                for (int c = 1; c <= n; ++c) {
                    ans[(c + k - 1) % n][i] = c;
                    ans[n + c - 1][i] = c;
                }
            }
            for (int i = 0; i < 2 * n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[i][j] << " ";
                }
                cout << endl;
            }

        }
	}
	return 0;
}
