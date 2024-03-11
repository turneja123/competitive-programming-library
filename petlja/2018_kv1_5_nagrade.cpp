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
const int N = 1005;
bool g[N][6 * N];
int sols[N];
vector <int> primes;
void eratosten(int n)
{
    bool composite[n];
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
bool bpm(int u, bool seen[], int match[], int m)
{
    for (int v = 0; v < m; v++)
    {
        if (g[u][v] && !seen[v])
        {
            seen[v] = true;
            if (match[v] < 0 || bpm(match[v], seen, match, m))
            {
                match[v] = u;
                sols[u] = v;
                return true;
            }
        }
    }
    return false;
}

int main()
{
amfetamin;
int n;
cin >> n;
int c[n];
eratosten(2e5 + 5);
map <int,int> mp;
for (int i = 0; i < n; i++)
{
    int a;
    cin >> a;
    c[i] = a;
    int smurf = a;
    for (int j = 0; j < primes.size(); j++)
    {
        if (a % primes[j] == 0)
        {
            auto it = mp.find(a / primes[j]);
            int cur;
            if (it == mp.end())
            {
                int sz = mp.size();
                mp.insert({a / primes[j], sz});
                cur = sz;
            }
            else
                cur = it -> second;
            g[i][cur] = 1;
        }
    }
}
int match[mp.size()];
memset(match, -1, sizeof(match));
int sol = 0;
for (int i = 0; i < mp.size(); i++)
{
    bool seen[mp.size()] = { };
    if (bpm(i, seen, match, mp.size()))
        sol++;
}
if (sol < n)
    cout << -1;
else
{
    for (int i = 0; i < n; i++)
    {
        for (auto it = mp.begin(); it!= mp.end(); ++it)
        {
            if (sols[i] == it->second)
            {
                cout << c[i] / it->first << " ";
                break;
            }
        }
    }
}
}
