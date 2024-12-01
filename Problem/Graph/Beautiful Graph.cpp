//https://codeforces.com/contest/1093/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e5 + 5;
const long long M = 998244353;

vector<int> adj[N];
bool vis[N];
int sz[N];
int depth[N];
bool can = true;
int comp = 0;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void dfs(int u) {
    vis[u] = true;
    comp++;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            sz[depth[v]]++;
            dfs(v);
        } else if (abs(depth[u] - depth[v]) % 2 == 0) {
            can = false;
        }
    }
    return;
}


int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        long long ans = 1;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                comp = 0;
                depth[i] = 0, sz[0]++;
                dfs(i);
                int s = 0;
                for (int i = 0; i < comp; i += 2) {
                    s += sz[i];
                }
                ans = ans * (modPow(2, s) + modPow(2, comp - s)) % M;
                for (int i = 0; i < comp; i++) {
                    sz[i] = 0;
                }
            }
        }
        if (!can) {
            ans = 0;
        }

        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            depth[i] = 0, sz[i] = 0, vis[i] = 0;
            adj[i].clear();
        }
        can = true;
	}
	return 0;
}
