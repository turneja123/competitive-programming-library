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
int sol[N];
int main()
{
    amfetamin;
    int n, s;
    cin >> n >> s;
    int tot = n * (n - 1) / 2;
    if (s > tot)
    {
        cout << -1;
        return 0;
    }
    for (int i = 1; i < n; i++)
    {
        if (tot - 2 * (n - i) >= s)
        {
            sol[i] = sol[i - 1] - 1;
            tot -= 2 * (n - i);
        }
        else
            sol[i] = sol[i - 1] + 1;
    }
    if (tot != s)
        cout << -1;
    else
        for (int i = 0; i < n; i++)
            cout << sol[i] << endl;
}
