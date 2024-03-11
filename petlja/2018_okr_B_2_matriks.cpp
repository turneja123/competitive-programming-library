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
const int N = 1e6 + 5;
int calcxor(int l, int r)
{
    int ret = 0;
    for (int i = 1; i < 31; i++)
    {
        int cur = 1 << i;
        int sum = 0;
        if (r < cur)
            break;
        if ((int)(l & cur) != 0)
        {
            int d = l / cur;
            sum += cur * (d + 1) - l;
        }
        if ((int)(r & cur) != 0)
        {
            int d = r / cur;
            sum += r - d * cur + 1;
        }

        if (sum % 2 == 1)
            ret += cur;
    }
    int ct = 0;
    if (l == r)
    {
        if (l % 2 == 1)
            ct++;
    }
    else
    {
        if (l % 2 == 1)
        {
            ct++;
            l++;
        }
        if (r % 2 == 1)
        {
            ct++;
            r--;
        }
        ct += (r - l) / 2;
    }
    if (ct % 2 == 1)
        ret++;

    return ret;

}
int main()
{
    amfetamin;
    int n, m, q;
    cin >> n >> m >> q;
    while (q--)
    {
        int yl, xl, yr, xr;
        cin >> yl >> xl >> yr >> xr;
        int sol = 0;
        if ((xr - xl) % 2 == 0)
            sol ^= calcxor(yl, yr);
        if ((yr - yl) % 2 == 0)
            sol ^= calcxor(xl, xr);
        cout << sol << endl;
    }

}
