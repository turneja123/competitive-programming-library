//solution for https://www.codechef.com/problems/SCALSUM
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
using namespace std;
using namespace __gnu_pbds;
const int N = 3e5+5;
const ll M = 4294967296;
list <int> adj[N];
ll w[N];
int parent[N];
int depth[N];
bool visited[N];
map <pair<int, int>, ll> mp;
vector <int> layer[N];
int sz = 1;
int ind[N];
vector <ll> sols[N];
bool sel[N];
void dfs(int v)
{
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
    {
        if (!visited[*it])
        {
            visited[*it] = true;
            depth[*it] = depth[v] + 1;
            sz = max(sz, depth[*it] + 1);
            layer[depth[*it]].push_back(*it);
            ind[*it] = layer[depth[*it]].size() - 1;
            parent[*it] = v;
            dfs(*it);
        }
    }
}
ll calc(int a, int b)
{
    ll cur = 0;
    while (true)
    {
        int dp = depth[a];
        if (sel[dp] == true)
        {
            int s = layer[dp].size();
            cur += sols[dp][ind[a] * s + ind[b]];
            cur = cur % M;
            break;
        }
        cur += w[a] * w[b];
        cur = cur % M;
        a = parent[a];
        b = parent[b];
        if (a == -1 && b == -1)
            break;
    }
    return cur;
}
int main()
{
    amfetamin;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> w[i];
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    parent[0] = -1;
    visited[0] = true;
    depth[0] = 0;
    ind[0] = 0;
    layer[0].push_back(0);
    dfs(0);
    int sqr = sqrt(sz);
    for (int i = 0; i < sz; i++)
    {
        int j = i * sqr;
        int mn = n;
        int koji = -1;
        for (j; j < min(sz, (i + 1) * sqr); j++)
        {
            int s = layer[j].size();
            if (s < mn)
            {
                mn = s;
                koji = j;
            }
        }
        if (layer[koji].size() <= 1000)
        {
            for (int k1 = 0; k1 < layer[koji].size(); k1++)
            {
                for (int k2 = 0; k2 < layer[koji].size(); k2++)
                {
                    int a = layer[koji][k1];
                    int b = layer[koji][k2];
                    ll c = calc(a, b);
                    sols[koji].push_back(c);
                }
            }
            sel[koji] = true;
        }
        if (j == sz)
            break;
    }
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        ll sol = calc(a, b);
        cout << sol << endl;
    }
}
