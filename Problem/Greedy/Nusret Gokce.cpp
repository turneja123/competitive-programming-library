//https://qoj.ac/contest/2511/problem/14118
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	vector<int> a(n), vis(n);
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        pq.push({a[i], i});
	}
	while (pq.size()) {
        auto [_, i] = pq.top();
        pq.pop();
        if (vis[i]) {
            continue;
        }
        vis[i] = 1;
        for (int di = -1; di <= 1; di++) {
            if (abs(di) == 1 && i + di >= 0 && i + di < n && a[i] - a[i + di] > m) {
                a[i + di] += a[i] - a[i + di] - m;
                pq.push({a[i + di], i + di});
            }
        }
	}
	for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
	}

	return 0;
}
