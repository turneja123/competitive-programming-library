//https://www.spoj.com/problems/SELECTION/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2505;

vector<int> a[N];
int l[N];

int main() {
	IOS;
	int n, m, k;
	cin >> n >> m >> k;
	int mx = 0;
	priority_queue<pair<int, pair<int, int>>> pq;
	for (int i = 0; i < n; i++) {
        a[i].resize(m);
        int x, b, c;
        cin >> a[i][0] >> x >> b >> c;
        for (int j = 1; j < m; j++) {
            a[i][j] = ((long long)x * a[i][j - 1] + b) % c;
        }
        sort(a[i].begin(), a[i].end());
        mx = max(mx, a[i][k - 1]);
        pq.push(make_pair(-a[i][0], make_pair(i, 0)));
	}
	int mn = -pq.top().first;
	int ans = mx - mn;
	bool stop = false;
	while (pq.size()) {
        while (-pq.top().first == mn) {
            int i = pq.top().second.first, j = pq.top().second.second;
            pq.pop();
            j++;
            if (j + k - 1 == m) {
                stop = true;
                break;
            }
            mx = max(mx, a[i][j + k - 1]);
            pq.push(make_pair(-a[i][j], make_pair(i, j)));
        }
        if (stop) {
            break;
        }
        mn = -pq.top().first;
        ans = min(ans, mx - mn);
	}
	cout << ans;

	return 0;
}
