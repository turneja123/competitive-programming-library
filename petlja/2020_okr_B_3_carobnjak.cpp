#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 5e5 + 5;
ll s[N];
int main()
{
amfetamin;
int n;
cin >> n;
ll e;
cin >> e;
priority_queue <ll> pq;
for (int i = 0; i < n; i++)
{
    ll a;
    cin >> a;
    pq.push(a);
}
ll sum = 0;
int sol = 0;
for (int i = 0; i < n; i++)
{
    cin >> s[i];
    sum += s[i];
}
sort(s, s + n, greater<ll>());
while (pq.size())
{
    if (sum >= e)
        break;
    ll a = pq.top();
    pq.pop();
    e -= a;
    a /= 2;
    if (a)
        pq.push(a);
    sol++;
}
if (e > 0)
{
    int p = 0;
    while (e > 0)
    {
        if (pq.size() && pq.top() > s[p])
        {
            ll a = pq.top();
            pq.pop();
            e -= a;
            a /= 2;
            if (a)
                pq.push(a);
        }
        else
            e -= s[p++];
        sol++;
    }
}
cout << sol;



}
