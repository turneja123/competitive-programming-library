//https://qoj.ac/contest/2509/problem/14091
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const ll M = 998244353;

int c[N];
ll dp[N][2 * N];
ll conv[2 * N];
int freq[N];
int val[N];
int sz[N];
vector<int> adj[N];

ll ans = 0;

int get_ind(int j) {
    if (j >= 0) {
        return j;
    }
    return 2 * N + j;
}

void dfs(int u, int p, int k) {
    val[u] = (c[u] == k ? 1 : -1);
    dp[u][get_ind(val[u])] = 1;
    dp[u][get_ind(-val[u])] = 0;
    dp[u][0] = 0;
    sz[u] = 1;

    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u, k);
        for (int i = -sz[u]; i <= sz[u]; i++) {
            for (int j = -sz[v]; j <= sz[v]; j++) {
                if (abs(i + j) <= freq[k]) {
                    conv[get_ind(i + j)] = (conv[get_ind(i + j)] + dp[u][get_ind(i)] * dp[v][get_ind(j)]) % M;
                }
            }
            conv[get_ind(i)] = (conv[get_ind(i)] + dp[u][get_ind(i)]) % M;
        }
        sz[u] = min(freq[k], sz[u] + sz[v]);
        for (int i = -sz[u]; i <= sz[u]; i++) {
            dp[u][get_ind(i)] = conv[get_ind(i)];
            conv[get_ind(i)] = 0;
        }

    }
    for (int i = 1; i <= sz[u]; i++) {
        ans = (ans + dp[u][i]) % M;
    }
}

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        cin >> c[i];
        freq[c[i]]++;
	}
	for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
        if (freq[i] == 1) {
            ans = (ans + 1) % M;
        } else if (freq[i] > 1) {
            dfs(0, 0, i);
        }
	}
	cout << ans;


	return 0;
}
