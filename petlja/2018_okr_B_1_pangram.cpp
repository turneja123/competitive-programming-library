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
void next(int &j, bool b[])
{
    while (b[j])
        j++;
}
int main()
{
    amfetamin;
    bool b[26] = { };
    int n;
    string s;
    cin >> n >> s;
    int q = 0;
    int let = 26;
    int j = 0;
    if (n < 26)
    {
        cout << "SAN";
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (s[i] != '?' && s[i] != '_' && b[s[i] - 'a'])
        {
            cout << "SAN";
            return 0;
        }
        if (s[i] != '?' && s[i] != '_')
        {
            b[s[i] - 'a'] = true;
            let--;
        }
        if (s[i] == '?')
            q++;
    }
    next(j, b);
    if (s[0] == '?')
    {
        if (j == 26)
        {
            cout << "SAN";
            return 0;
        }
        s[0] = 'a' + j;
        b[j] = true;
        next(j, b);
        let--;
        q--;
    }
    if (s[n - 1] == '?')
    {
        if (j == 26)
        {
            cout << "SAN";
            return 0;
        }
        s[n - 1] = 'a' + j;
        b[j] = true;
        next(j, b);
        let--;
        q--;
    }
    if (q < let)
    {
        cout << "SAN";
        return 0;
    }
    for (int i = 1; i < n - 1; i++)
    {
        if (s[i] != '?')
            continue;
        if (q < let)
        {
            cout << "SAN";
            return 0;
        }
        if (let == 0 && (s[i - 1] == '_' || s[i + 1] == '_'))
        {
            cout << "SAN";
            return 0;
        }
        if (let == q || (s[i - 1] == '_' || s[i + 1] == '_'))
        {
            s[i] = 'a' + j;
            b[j] = true;
            next(j, b);
            let--;
            q--;
        }
        else
        {
            s[i] = '_';
            q--;
        }
    }
    cout << s;
}
