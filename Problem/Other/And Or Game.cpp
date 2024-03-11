//solution for https://www.codechef.com/JAN21B/problems/ORAND
//subtask 1
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
const int N = 2000;
int a[N];
int b[N];
bool bl[N];
bool vis[N];
void f(int k, int m)
{
    for (int i = 0; i < N; i++)
        if (bl[i] && !vis[k | i])
        {
            vis[k | i] = true;
            f(k | i, m);
        }
    for (int i = 0; i < m; i++)
        if (!vis[k & b[i]] )
        {
            vis[k & b[i]] = true;
            f(k & b[i], m);
        }
}
int main()
{
    amfetamin;
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < N; i++)
        {
            bl[i] = false;
            vis[i] = false;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            bl[a[i]] = true;
        }
        for (int i = 0; i < m; i++)
            cin >> b[i];
        for (int i = 0; i < n; i++)
            f(a[i], m);
        bl[0] = true;
        int sol = 0;
        for (int i = 0; i < N; i++)
            if (bl[i] || vis[i])
                sol++;
        cout << sol << endl;
    }
}
