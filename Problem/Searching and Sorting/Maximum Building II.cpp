//https://cses.fi/problemset/task/1148/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> r(n + 2, vector<int>(m + 2));
	vector<vector<int>> u(n + 1, vector<int>(m + 1));
	vector<vector<int>> d(n + 1, vector<int>(m + 1));
	vector<vector<int>> ans(n + 3, vector<int>(m + 3));
	vector<vector<char>> mat(n + 1, vector<char>(m + 1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
		for (int j = m; j >= 1; j--) {
			if (mat[i][j] == '*') {
				r[i][j] = 0;
			} else {
				r[i][j] = r[i][j + 1] + 1;
			}
		}
	}

	stack<int> st;
	for (int j = 1; j <= m; j++) {
		while (!st.empty()) {
            st.pop();
        }
		for (int i = 1; i <= n; i++) {
			while (!st.empty() && r[i][j] < r[st.top()][j]) {
                st.pop();
            }
			u[i][j] = st.empty() ? 1 : (st.top() + 1);
			st.push(i);
		}
		while (!st.empty()) {
            st.pop();
        }
		for (int i = n; i >= 1; i--) {
			while (!st.empty() && r[i][j] <= r[st.top()][j]) {
                st.pop();
            }
			d[i][j] = st.empty() ? n : (st.top() - 1);
			st.push(i);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans[1][r[i][j]]++;
			ans[i - u[i][j] + 2][r[i][j]]--;
			ans[d[i][j] - i + 2][r[i][j]]--;
			ans[d[i][j] - u[i][j] + 3][r[i][j]]++;
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; ++i) {
            ans[i][j] += ans[i - 1][j];
        }
		for (int i = 1; i <= n; ++i) {
            ans[i][j] += ans[i - 1][j];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = m; j >= 2; --j) {
            ans[i][j - 1] += ans[i][j];
        }
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; ++j) {
            cout << ans[i][j] << " ";
        }
		cout << endl;
	}

    return 0;
}
