//solution for
//https://www.hackerearth.com/practice/algorithms/dynamic-programming/2-dimensional/practice-problems/algorithm/minimum-cost-path-in-a-grid-2-2e1df6ef/
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
const int M = 1e5 + 5;
const int INF = 2e9;
const int SQRT = sqrt(M);
int grid[N][N];
int dp[N][N];
int val[M];
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
int main()
{
    amfetamin;
    eratosten(SQRT);
    for (int i = 2; i <= M; i++)
    {
        int ct = 0;
        int temp = i;
        for (int j = 0; j < primes.size(); j++)
        {
            while (temp % primes[j] == 0)
            {
                temp /= primes[j];
                ct++;
            }
        }
        if (temp > 1)
            ct++;
        val[i] = ct;
    }
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                cin >> grid[i][j];
                grid[i][j] = val[grid[i][j]];
                dp[i][j] = INF;
            }
        dp[0][0] = grid[0][0];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                if (j != 0)
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
                if (i != 0)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
            }
        cout << dp[n - 1][m - 1] << endl;
    }
}
