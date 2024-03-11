#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
const int N = 2e5 + 5;
ll sum[N];
ll arr[N];
map <ll, ll> mp[N];

ll calc(map <ll, ll> a, map <ll, ll> b, ll sum)
{
    ll ret = 0;
    for (auto j = a.begin(); j != a.end(); ++j)
    {
        auto it = b.find(j->first + sum);
        if (it != b.end())
            ret += j->second * it->second;
    }
    return ret;
}
ll sve(int n)
{
    ll ret = 0;
    map <ll, ll> m;
    for (int i = 0; i < n; i++)
    {
        auto it = m.find(arr[i]);
        if (it == m.end())
            m.insert({arr[i] , 1});
        else
            it->second++;
    }
    for (auto it = m.begin(); it != m.end(); ++it)
        ret += (it->second) * (it->second - 1) / 2;
    return ret;
}
int main()
{
amfetamin;
int n, l;
cin >> n >> l;
for (int i = 0; i < n; i++)
{
    int a;
    cin >> a;
    sum[i % l] += a;
    auto it = mp[i % l].find(a);
    if (it == mp[i % l].end())
        mp[i % l].insert({a , 1});
    else
        it->second++;
    arr[i] = a;
}
if (l == 2)
{
    ll sol = 0;
    if (sum[1] > sum[0] && (sum[1] % 2 == sum[0] % 2))
        sol = calc(mp[0], mp[1], (sum[1] - sum[0]) / 2);
    else
    if (sum[0] > sum[1] && sum[1] % 2 == sum[0] % 2)
        sol = calc(mp[1], mp[0], (sum[0] - sum[1]) / 2);
    else
    if (sum[0] == sum[1])
        sol = sve(n);
    cout << sol;
    return 0;
}
if (l == 3)
{
    ll sol;
    pair <ll ,ll> s[3];
    s[0] = {sum[0], 0};
    s[1] = {sum[1], 1};
    s[2] = {sum[2], 2};
    sort(s, s + 3);
    if (s[0].first == s[1].first && s[1].first != s[2].first)
    {
        cout << 0;
        return 0;
    }
    if (s[0].first == s[1].first && s[1].first == s[2].first)
    {
        sol = sve(n);
        cout << sol;
        return 0;
    }
    if (!(s[1].first - s[0].first == s[2].first - s[1].first))
    {
        cout << 0;
        return 0;
    }
    sol = calc(mp[s[0].second], mp[s[2].second], s[1].first - s[0].first);
    cout << sol;
    return 0;
}
map <ll, ll> sums;
for (int i = 0; i < l; i++)
{
    auto it = sums.find(sum[i]);
    if (it == sums.end())
        sums.insert({sum[i] , 1});
    else
        it->second++;
}
if (sums.size() == 1)
{
    ll sol = sve(n);
    cout << sol;
    return 0;
}
if (sums.size() == 3)
{
    bool bo = false;
    ll koji = 0;
    for (auto it = sums.begin(); it != sums.end(); ++it)
    {
        if (it->second != 1 && bo)
        {
            cout << 0;
            return 0;
        }
        if (it->second != 1 && bo == false)
        {
            bo = true;
            koji = it->first;
        }
    }
    int lf = -1;
    int rt = -1;
    for (int i = 0; i < l; i++)
    {
        if (sum[i] != koji && lf == -1)
            lf = i;
        else
        if (sum[i] != koji)
            rt = i;
    }
    if (sum[lf] > sum[rt])
        swap(lf, rt);
    if (!(koji - sum[lf] == sum[rt] - koji))
    {
        cout << 0;
        return 0;
    }
    ll sol = calc(mp[lf], mp[rt], koji - sum[lf]);
    cout << sol;
    return 0;
}

cout << 0;
return 0;

}


