//https://qoj.ac/contest/2511/problem/14105
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<int> pos[26];

int main() {
	IOS;
	string a, b;
	cin >> a >> b;
	int n = a.size(), m = b.size();
	a = a + a;
	for (int i = 0; i < 2 * n; i++) {
        pos[a[i] - 'a'].push_back(i);
	}
	int ans = 1, j = *lower_bound(pos[b[0] - 'a'].begin(), pos[b[0] - 'a'].end(), 0);
	for (int i = 1; i < m; i++) {
        int nx = *upper_bound(pos[b[i] - 'a'].begin(), pos[b[i] - 'a'].end(), j);
        if (nx >= n) {
            ans++;
            nx -= n;
        }
        j = nx;
	}
	cout << ans;

	return 0;
}
