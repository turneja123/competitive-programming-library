//solution for https://www.codechef.com/DEC20B/problems/HXOR
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
const int N = 1e5 + 5;
vector <int> bit[32];
int main()
{
    amfetamin;
    int t;
    cin >> t;
    while (t--)
    {
        int n, x;
        cin >> n >> x;
        int a[n];
        int sol[n];
        int ct[32] = { };
        int p[32] = { };
        for (int i = 0; i < n; i++)
        {
            int c;
            cin >> c;
            a[i] = c;
            sol[i] = c;
            int j = 0;
            while (c > 0)
            {
                int cur = c % 2;
                c /= 2;
                if (cur == 1)
                {
                    ct[j]++;
                    bit[j].push_back(i);
                }
                j++;
            }
        }
        for (int i = 0; i < n - 1; i++)
            for (int j = 30; j >= 0; j--)
            {
                if (x == 0)
                    goto zavrsi;
                if (p[j] != bit[j].size() && bit[j][p[j]] == i)
                {
                    p[j]++;
                    if (p[j] != bit[j].size())
                    {
                        int dr = bit[j][p[j]];
                        p[j]++;
                        x--;
                        sol[i] ^= 1 << j;
                        sol[dr] ^= 1 << j;
                    }
                    else
                    {
                        x--;
                        sol[i] ^= 1 << j;
                        sol[n - 1] ^= 1 << j;
                    }
                }
            }
        zavrsi:;
        if (x == 0)
        {
            for (int i = 0; i < n; i++)
                cout << sol[i] << " ";
            cout << endl;
        }
        else
        {

            int l = 0;
            for (int i = 0; i < 32; i++)
                if (ct[i] % 2 == 1)
                    l += 1 << i;
            if (n == 2 && x % 2 == 1)
                cout << 1 << " " << (l ^ 1) << endl;
            else
            {
            for (int i = 0; i < n - 1; i++)
                cout << 0 << " ";

                cout << l << endl;
            }

        }
        for (int i = 0; i < 32; i++)
            bit[i].erase(bit[i].begin(), bit[i].end());
    }

}
