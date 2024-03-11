//solution for https://atcoder.jp/contests/abc188/tasks/abc188_d
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
const int N = 2e5 + 5;
tuple <ll, ll, ll> t[N];
int main()
{
    amfetamin;
    ll n, c;
    cin >> n >> c;
    for (int i = 0; i < n; i++)
    {
        ll a, b, cst;
        cin >> a >> b >> cst;
        get<0>(t[i]) = a;
        get<1>(t[i]) = b;
        get<2>(t[i]) = cst;
    }
    sort(t, t + n);
    ll sol = 0;
    ll curcost = 0;
    ll curday = get<0>(t[0]);
    priority_queue <pair<int, ll>> pq;
    for (int i = 0; i < n; i++)
    {
        while (pq.size() && -pq.top().first < get<0>(t[i]))
        {
            sol += min(curcost, c) * (-pq.top().first - curday + 1);
            curday = -pq.top().first + 1;
            curcost -= pq.top().second;
            pq.pop();
        }
        pq.push({-get<1>(t[i]), get<2>(t[i])});
        sol += min(curcost, c) * (get<0>(t[i]) - curday);
        curday = get<0>(t[i]);
        curcost += get<2>(t[i]);
    }
    while (pq.size())
    {
        sol += min(curcost, c) * (-pq.top().first - curday + 1);
        curday = -pq.top().first + 1;
        curcost -= pq.top().second;
        pq.pop();
    }

    cout << sol;

}
