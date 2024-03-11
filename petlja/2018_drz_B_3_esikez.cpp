#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 2e5 + 5;
int sma[N];
int smb[N];
unordered_set <int> ba;
unordered_set <int> bb;
unordered_map <int,int> mp;
vector <int> a;
vector <int> b;
ll seg[2 * N];
void build(int n)
{
    for (int i = 0; i < n; i++)
        seg[i + n] = 0;
    for (int i = n - 1; i > 0; i--)
        seg[i] = 0;
}
void update(int pos, int val, int n)
{
    pos += n;
    seg[pos] = val;
    while (pos > 1)
    {
        pos /= 2;
        seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]);
    }
}
ll rmq(int l, int r, int n)
{
    l += n;
    r += n;
    ll mx = 0;
    while (l < r)
    {
        if (r % 2 == 1)
            mx = max(mx, seg[--r]);
        if (l % 2 == 1)
            mx = max(mx, seg[l++]);
        l /= 2;
        r /= 2;
    }
    return mx;
}
int main()
{
amfetamin;
int n, m;
cin >> n >> m;
for (int i = 0; i < n; i++)
{
    cin >> sma[i];
    ba.insert(sma[i]);
}
for (int i = 0; i < m; i++)
{
    cin >> smb[i];
    bb.insert(smb[i]);
}
for (int i = 0; i < n; i++)
{
    if (bb.find(sma[i]) != bb.end())
    {
        a.push_back(sma[i]);
        mp.insert({sma[i], a.size() - 1});
    }
}
for (int i = 0; i < m; i++)
{
    if (ba.find(smb[i]) != ba.end())
        b.push_back(smb[i]);
}

int sol = n - a.size() + m - b.size();
n = a.size();
build(n);
int mx = 0;
for (int i = 0; i < n; i++)
{
    auto it = mp.find(b[i]);
    int pos = it->second;
    int r = rmq(0, pos + 1, n);
    mx = max(mx, r + 1);
    update(pos, r + 1, n);
}
sol += 2 * (n - mx);
cout << sol;
}
