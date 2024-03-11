//solution for
//https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/matrix-and-xor-operation-a2e19185/editorial/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 1005;
const ll M = 1e9 + 7;
int main()
{
    amfetamin;
    int t;
    cin >> t;
    while (t--)
    {
        ll n, m, k;
        cin >> n >> m >> k;
        bool b = false;
        for (int i = 0; i <= n / 2; i++)
        {
            if (i == n / 2 && n % 2 == 0)
            {
                if (k == n * m / 2)
                    b = true;
                continue;
            }
            ll p = (k - m * i) / (n - 2 * i);
            ll mod = (k - m * i) % (n - 2 * i);
            if (mod == 0 && p <= m && p >= 0)
                b = true;
        }
        int temp = n;
        if (b)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}
