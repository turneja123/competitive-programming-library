//https://codeforces.com/contest/2110/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

vector<pair<int, int>> adj[N];
vector<int> ans;

int deg[N];
bool vis[N];

void dfs(int u) {
    while (adj[u].size()) {
        auto [v, e] = adj[u].back();
        adj[u].pop_back();
        if (vis[e]) {
            continue;
        }
        vis[e] = true;
        dfs(v);
    }
    ans.push_back(u);
    return;
}

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int m;
        cin >> m;
        vector<pair<int, int>> ivals;
        map<int, int> mpx, mpy;
        map<pair<int, int>, int> id;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            auto itx = mpx.find(u);
            if (itx == mpx.end()) {
                mpx[u] = mpx.size();
            }
            auto ity = mpy.find(v);
            if (ity == mpy.end()) {
                mpy[v] = mpy.size();
            }
            u = mpx[u], v = mpy[v];
            id[make_pair(u, v)] = i;
            ivals.push_back(make_pair(u, v));
        }
        for (int i = 0; i < m; i++) {
            auto [u, v] = ivals[i];
            v += mpx.size();
            adj[u].push_back(make_pair(v, i));
            adj[v].push_back(make_pair(u, i));
            deg[u]++;
            deg[v]++;

        }
        int n = mpx.size() + mpy.size();
        bool can = true;
        int st = -1, en = -1;
        for (int i = 0; i < n; i++) {
            if (deg[i] % 2 == 1) {
                if (st == -1) {
                    st = i;
                } else if (en == -1) {
                    en = i;
                } else {
                    can = false;
                }
            }
        }
        if (st != -1 && en == -1) {
            can = false;
        }
        if (!can) {
            cout << "NO" << endl;
        } else {
            if (st == -1) {
                st = 0;
            }
            dfs(st);
            reverse(ans.begin(), ans.end());
            if (ans.size() != m + 1) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
                for (int i = 1; i < ans.size(); i++) {
                    int x = ans[i - 1], y = ans[i];
                    if (x > y) {
                        swap(x, y);
                    }
                    y -= mpx.size();
                    cout << id[make_pair(x, y)] + 1 << " ";
                }
                cout << endl;
            }
        }
        ans.clear();
        for (int i = 0; i <= max(n, m); i++) {
            adj[i].clear();
            vis[i] = false;
            deg[i] = 0;
        }
	}
	return 0;
}
