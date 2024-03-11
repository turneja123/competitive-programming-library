//solution for https://atcoder.jp/contests/abc188/tasks/abc188_e
#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 2e5 + 5;
const int INF = 1e9 + 5;
int sol = -INF;
int a[N];
int mx[N];
bool vis[N];
list <int> adj[N];
int dfs(int v)
{
    if (vis[v])
        return mx[v];
    mx[v] = -INF;
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
        mx[v] = max(mx[v], dfs(*it));
    sol = max(sol, mx[v] - a[v]);
    mx[v] = max(mx[v], a[v]);
    return mx[v];
}
int main()
{
    amfetamin;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }
    for (int i = 0; i < n; i++)
        dfs(i);
    cout << sol;
}
