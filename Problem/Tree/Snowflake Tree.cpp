//https://atcoder.jp/contests/abc385/tasks/abc385_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<int> adj[N];
int deg[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        vector<int> d;
        for (int v : adj[i]) {
            d.push_back(deg[v]);
        }
        sort(d.begin(), d.end(), greater<int>());
        for (int j = 0; j < deg[i]; j++) {
            ans = max(ans, d[j] * (j + 1) + 1);
        }
    }
    cout << n - ans;

    return 0;
}
