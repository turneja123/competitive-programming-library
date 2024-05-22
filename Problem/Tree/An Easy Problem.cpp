//https://www.spoj.com/problems/ADDAP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 1e9 + 7;

long long x[N];
long long y[N];
long long ans[N];
vector<int> adj[N];

void dfs(int u, long long sum, long long inc, int p) {
    sum = (sum + x[u] + inc) % M;
    ans[u] = sum;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, sum, (inc + y[u]) % M, u);
        }
    }
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u; long long a, b;
        cin >> u >> a >> b;
        u--; x[u] += a, y[u] += b;
    }
    dfs(0, 0, 0, -1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
