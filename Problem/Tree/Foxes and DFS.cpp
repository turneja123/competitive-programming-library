//https://eolymp.com/en/problems/12287
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int ans = 0;

int one_suf[N];
int one_pref[N];
int one_entire[N];

int dp_suf[N];
int dp_pref[N];
int dp_entire[N];

vector<int> adj[N];

void dfs(int u, int p) {

    dp_entire[u] = one_entire[u];

    int add = 0;
    vector<pair<int, int>> l, r;

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            dp_entire[u] &= dp_entire[v];
            if (dp_entire[v]) {
                add += dp_pref[v];
            } else {
                l.push_back({dp_suf[v], v});
                r.push_back({dp_pref[v], v});
            }
        }
    }
    if (l.size()) {
        sort(l.begin(), l.end());
        sort(r.begin(), r.end());
        reverse(l.begin(), l.end());
        reverse(r.begin(), r.end());
        while (l.size() > 2) {
            l.pop_back();
        }
        while (r.size() > 2) {
            r.pop_back();
        }
        for (auto [d1, x] : l) {
            for (auto [d2, y] : r) {
                if (x != y) {
                    ans = max(ans, d1 + add + d2);
                }
            }
        }
    }
    ans = max(ans, one_suf[u] + add + (r.size() == 0 ? 0 : r[0].first));
    if (one_entire[u]) {
        dp_pref[u] = one_pref[u] + add + (r.size() == 0 ? 0 : r[0].first);
    } else {
        dp_pref[u] = one_pref[u];
    }
    if (l.size()) {
        dp_suf[u] = l[0].first + add;
    } else {
        dp_suf[u] = one_suf[u] + add;
    }
}

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
        int n = i;
        vector<int> cur;
        while (n > 0) {
            if (n % 10 == 1 || n % 10 == 7) {
                cur.push_back(1);
            } else {
                cur.push_back(0);
            }
            n /= 10;
        }
        reverse(cur.begin(), cur.end());
        int j = 0;
        while (j < cur.size() && cur[j] == 1) {
            j++;
        }
        one_pref[i] = j;
        if (j == cur.size()) {
            one_suf[i] = j;
            one_entire[i] = 1;
        } else {
            one_entire[i] = 0;
            j = 0;
            while (j < cur.size() && cur[cur.size() - 1 - j] == 1) {
                j++;
            }
            one_suf[i] = j;
        }
	}
	dfs(1, 1);
	cout << ans;

	return 0;
}
