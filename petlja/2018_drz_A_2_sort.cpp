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
int dfs(int n, list <int> adj[], bool vis[], int ct, int m)
{
    for (auto it = adj[n].begin(); it != adj[n].end(); ++it)
    {
        if (adj[n].size() > 2)
            return ct;
        if (adj[n].size() == 2 && n == 0)
            return ct;
        if (!vis[*it])
        {
            vis[*it] = true;
            return dfs(*it, adj, vis, ++ct, m);
        }
        if (ct == m)
            return ct;

    }
}
int main()
{
    amfetamin;
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            a[i]--;
        }
        int m;
        cin >> m;
        list <int> adj[m];
        for (int i = 0; i < m - 1; i++)
        {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        int i = n - 1;
        while (a[i] == i)
            i--;
        i++;
        bool vis[m] = { };
        vis[0] = true;
        int k = dfs(0, adj, vis, 1, m);
        if (m - k >= i)
            cout << "DA" << endl;
        else
            cout << "NE" << endl;
    }
}
