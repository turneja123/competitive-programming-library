//solution for
//https://www.hackerearth.com/challenges/competitive/january-circuits-21/algorithm/gcd-function-9fe49c14/
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
vector <int> primes;
void eratosten(int n)
{
    bool composite[n] = { };
    for (int i = 2; i <= n; i++)
    {
        if (!composite[i])
        {
            primes.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                composite[j] = true;
        }
    }
}
int _pow(ll a, ll y)
{
    ll ret = 1;
    while (y--)
        ret *= a;
    return ret;
}

int main()
{
    amfetamin;
    eratosten(40);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int sol = n * (n + 1) / 2;
        int *mx = (int *)malloc(sizeof(int) * primes.size());
        memset(mx, 0, sizeof(int) * primes.size());
        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j < primes.size(); j++)
            {
                if (primes[j] > i)
                    break;
                int temp = i;
                int ct = 0;
                while (temp % primes[j] == 0)
                {
                    ct++;
                    temp /= primes[j];
                }
                mx[j] = max(mx[j], ct);
            }
        }
        ll x = 1;
        for (int i = 0; i < primes.size(); i++)
            x *= _pow(primes[i], mx[i]);
        cout << sol << " " << x << endl;
    }

}
