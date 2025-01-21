//https://codeforces.com/gym/100589/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int B = 100;

vector<int> adj[N];
int sz[N];
int tour[N];
int pos[N];
int depth[N];
int euler = 0;

long long sum[N];
long long add[N];
vector<int> s[N];

int dfs(int v, int ct, int p) {
    pos[euler] = v;
    tour[v] = euler++;
    for (auto u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            ct += dfs(u, 1, v);
        }
    }
    return sz[v] = ct;
}

void rebuild(int u, int p) {
    sum[u] = add[depth[u]];
    for (auto v : adj[u]) {
        if (v != p) {
            rebuild(v, u);
            sum[u] += sum[v];
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 1, 0);
    for (int i = 0; i < n; i++) {
        int u = pos[i];
        s[depth[u]].push_back(i);
    }
    vector<pair<int, int>> buf;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, y;
            cin >> l >> y;
            buf.push_back(make_pair(l, y));
            add[l] += y;
        } else {
            int u;
            cin >> u;
            u--;
            long long ans = sum[u];
            for (int j = 0; j < buf.size(); j++) {
                auto [l, y] = buf[j];
                if (s[l].size() == 0) {
                    continue;
                }
                int R = (upper_bound(s[l].begin(), s[l].end(), tour[u] + sz[u] - 1) - s[l].begin());
                int L = (lower_bound(s[l].begin(), s[l].end(), tour[u]) - s[l].begin());
                int ct = R - L;
                ans += (long long)y * ct;
            }
            cout << ans << endl;
        }
        if (buf.size() > B) {
            rebuild(0, 0);
            buf.clear();
        }
    }
    return 0;
}
