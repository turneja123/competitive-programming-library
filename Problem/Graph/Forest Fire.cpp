//bbc18q
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int tim[N];
int ans[N];

vector<int> adj[N];
vector<int> moments[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        tim[i] = N;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < q; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 1) {
            tim[u] = min(tim[u], i);
        } else {
            ans[u]++;
            if (tim[u] == N) {
                moments[u].push_back(i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            ans[i] += lower_bound(moments[j].begin(), moments[j].end(), tim[i]) - moments[j].begin();
        }
        cout << ans[i] << endl;
    }

    return 0;
}
