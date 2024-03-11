#include <bits/stdc++.h>
#include <bits/stdtr1c++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<pair<ll, ll>,null_type,less<pair<ll,ll>>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 250005;
const int INF = 1e9 + 5;
ll mpx[N];
ll mpy[N];
ll segxV[2 * N];
ll segxPR[2 * N];
ll segyV[2 * N];
ll segyPR[2 * N];
ordered_set stx;
ordered_set sty;
vector <int> input[N];

void update(int pos, ll val, int n, ll seg[])
{
    pos += n;
    seg[pos] = val;
    while (pos > 1)
    {
        pos /= 2;
        seg[pos] = seg[2 * pos] + seg[2 * pos + 1];
    }
}
ll rsq(int l, int r, int n, ll seg[])
{
    l += n;
    r += n;
    ll sum = 0;
    while (l < r)
    {
        if (r % 2 == 1)
            sum += seg[--r];
        if (l % 2 == 1)
            sum += seg[l++];
        l /= 2;
        r /= 2;
    }
    return sum;
}

int main()
{
    amfetamin;
    int n, m;
    cin >> n >> m;
    int ct = 0;
    for (int i = 0; i < n; i++)
    {
        ll t, x, y;
        cin >> t >> x >> y;
        input[i].push_back(t);
        input[i].push_back(x);
        input[i].push_back(y);
        if (t == 1)
        {
            ll v;
            cin >> v;
            input[i].push_back(v);
            stx.insert({x, ct});
            sty.insert({y, ct});
            ct++;
        }
    }
    ct = 0;
    for (auto it = stx.begin(); it != stx.end(); ++it)
    {
        mpx[it->second] = ct;
        ct++;
    }
    int sz = ct;
    ct = 0;
    for (auto it = sty.begin(); it != sty.end(); ++it)
    {
        mpy[it->second] = ct;
        ct++;
    }
    ct = 0;
    for (int i = 0; i < n; i++)
    {
        ll x = input[i][1];
        ll y = input[i][2];
        if (input[i][0] == 1)
        {
            ll v = input[i][3];
            int indx = mpx[ct];
            int indy = mpy[ct];
            update(indx, v, sz, segxV);
            update(indx, x * v, sz, segxPR);
            update(indy, v, sz, segyV);
            update(indy, y * v, sz, segyPR);
            ct++;

        }
        else
        {
            int pos = stx.order_of_key({x, INF}) - 1;
            ll sumxL, sumxR;
            if (pos == -1)
                sumxL = 0;
            else
                sumxL = x * rsq(0, pos + 1, sz, segxV) - rsq(0, pos + 1, sz, segxPR);
            if (pos == sz - 1)
                sumxR = 0;
            else
                sumxR = rsq(pos + 1, sz, sz, segxPR) - x * rsq(pos + 1, sz, sz, segxV);
            ll sumx = sumxL + sumxR;

            pos = sty.order_of_key({y, INF}) - 1;
            ll sumyL, sumyR;
            if (pos == -1)
                sumyL = 0;
            else
                sumyL = y * rsq(0, pos + 1, sz, segyV) - rsq(0, pos + 1, sz, segyPR);
            if (pos == sz - 1)
                sumyR = 0;
            else
                sumyR = rsq(pos + 1, sz, sz, segyPR) - y * rsq(pos + 1, sz, sz, segyV);
            ll sumy = sumyL + sumyR;

            cout << sumx + sumy << endl;
        }
    }

}
