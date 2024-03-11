//solution for https://atcoder.jp/contests/abc183/tasks/abc183_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 2e5+5;
map <int, int> mp[N];
int c[N];
int parent[N];
int sz[N];
int dsu_find(int a)
{
    while (parent[a] != a) a = parent[a];
    return a;
}
void dsu_unite(int a, int b)
{
    if (sz[b] > sz[a]) swap(a, b);
    for (auto it = mp[b].begin(); it != mp[b].end(); ++it)
    {
        int koji = it->first;
        int koliko = it->second;
        auto i = mp[a].find(koji);
        if (i != mp[a].end())
            i->second += koliko;

        else
            mp[a].insert({koji, koliko});
    }
    sz[a] += sz[b];
    parent[b] = a;
}
void amfetamin()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cerr.tie(0);
}
int main()
{
    amfetamin();
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> c[i];
    for (int i = 0; i < n; i++)
        mp[i].insert({c[i], 1});
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < q; i++)
    {
        int k, a, b;
        cin >> k >> a >> b;
        if (k == 1)
        {
            a--;
            b--;
            int p1 = dsu_find(a);
            int p2 = dsu_find(b);
            if (p1 != p2)
                dsu_unite(p1, p2);
        }
        if (k == 2)
        {
            a--;
            int p = dsu_find(a);
            auto it = mp[p].find(b);
            if (it != mp[p].end())
                cout << it->second<<endl;
            else
                cout << 0 << endl;
        }
    }
}
