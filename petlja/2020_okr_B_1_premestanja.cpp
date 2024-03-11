#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define ll long long
#define pb push_back
#define endl "\n"
#define amfetamin ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); cerr.tie(0);
#define ordered_set tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
const int N = 3e5 + 5;
int a[N];
int main()
{
amfetamin;
int n, m, k;
cin >> n >> m >> k;
int ct = 0;
for (int i = 0; i < n; i++)
    a[i] = i;
for (int i = 0; i < m; i++)
{
    int l, r;
    cin >> l >> r;
    l--, r--;
    int tmp1 = a[l];
    int tmp2 = a[r];
    a[l] = a[r];
    if (abs(a[l] - l) > k && !(abs(tmp1 - l) > k))
        ct++;
    if (!(abs(a[l] - l) > k) && abs(tmp1 - l) > k)
        ct--;
    a[r] = tmp1;
    if (abs(a[r] - r) > k && !(abs(tmp2 - r) > k))
        ct++;
    if (!(abs(a[r] - r) > k) && abs(tmp2 - r) > k)
        ct--;
    if (ct)
        cout << 1 << endl;
    else
        cout << 0 << endl;
}


}
