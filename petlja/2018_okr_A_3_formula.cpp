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
string alph = "abcdefghijkl";

string maxMerge(string a, char b)
{
    string ret = "[" + a + "," + b + "]";
    return ret;
}
string minMerge(string a, string b)
{
    string ret = "(" + a + "," + b + ")";
    return ret;
}
int main()
{
    amfetamin;
    int n, k;
    cin >> n >> k;
    int pw = 1 << n;
    string sol = "";
    for (int i = 0; i < pw; i++)
    {
        if (__builtin_popcount(i) == k)
        {
            int curpw = 1;
            int ct = 0;
            string group = "";
            while (curpw < pw)
            {
                if ((int)(i & curpw) == curpw)
                {
                    if (group == "")
                        group = alph[ct];
                    else
                        group = maxMerge(group, alph[ct]);
                }
                ct++;
                curpw *= 2;
            }
            if (sol == "")
                sol = group;
            else
                sol = minMerge(sol, group);
        }
    }
    cout << sol;


}
