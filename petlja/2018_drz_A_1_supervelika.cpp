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
int main()
{
    amfetamin;
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        pair <int, int> l[m];
        int r[m];
        int k[m];
        int a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < m; i++)
        {
            int x;
            cin >> x;
            x--;
            l[i] = {x, i};
        }
        for (int i = 0; i < m; i++)
        {
            cin >> r[i];
            r[i]--;
        }
        for (int i = 0; i < m; i++)
            cin >> k[i];
        sort(l, l + m);
        priority_queue <pair<int, int>> pq;
        int j = 0;
        bool b = true;
        for (int i = 0; i < n; i++)
        {
            while (j < m && l[j].first == i)
            {
                int ind = l[j].second;
                pq.push({-r[ind], k[ind]});
                j++;
            }
            while (pq.size() && -pq.top().first < i)
                pq.pop();
            while (pq.size())
            {
                int pw = pq.top().second;
                int rt = pq.top().first;
                pq.pop();
                if (pw > a[i])
                {
                    pw -= a[i];
                    a[i] = 0;
                    pq.push({rt, pw});
                }
                else
                {
                    a[i] -= pw;
                    pw = 0;
                }
                if (a[i] == 0)
                    break;
            }
            if (a[i] != 0)
                b = false;
        }
        if (b)
            cout << "DA" << endl;
        else
            cout << "NE" << endl;
    }

}
