//solution for
//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/move-minimization-8a9d3991/
#pragma GCC target ("avx2")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
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
const int N = 7005;
const ll M = 1e9 + 7;
unsigned short int l[N][N];
unsigned short int r[N][N];
int main()
{
    amfetamin;
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i]--;
    }
    bool b[n] = {};
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            l[i][j] = sum;
            if (b[j])
                sum++;
        }
        b[a[i]] = true;
    }
    bool bb[n] = { };
    int inv = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            r[i][j] = sum;
            if (bb[j])
                sum++;
        }
        bb[a[i]] = true;
        inv += l[i][a[i]];
    }
    int sol = inv;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] > a[i])
                continue;
            int temp = sol;
            sol = min(sol, inv - r[i][a[i]] - r[j][a[j]] - l[i][a[i]] - l[j][a[j]]
                      + r[i][a[j]] + l[i][a[j]] + l[j][a[i]] + r[j][a[i]] + 1);
        }
    cout << sol;

}
