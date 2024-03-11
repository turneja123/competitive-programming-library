#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
int main()
{
amfetamin;
int n;
cin >> n;
int ct[26] = { };
char c;
cin >> c;
ct[c - 'A']++;
int i = 1;
for (i; i < n; i++)
{
    string s;
    cin >> s;
    bool b = false;
    int nw;
    int f[26] = { };
    for (int j = 0; j <= i; j++)
        f[s[j] - 'A']++;
    for (int j = 0; j < 26; j++)
    {
        if (f[j] != ct[j] && f[j] != ct[j] + 1)
            goto br;
        if (f[j] == ct[j] + 1 && b)
            goto br;
        if (f[j] == ct[j] + 1)
        {
            b = true;
            nw = j;
        }
    }
    ct[nw]++;
}
br: cout << i;
}


