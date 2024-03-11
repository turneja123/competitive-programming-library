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
int a[N];
int main()
{
amfetamin;
int n;
cin >> n;
multiset <int> st;
for (int i = 0; i < n; i++)
{
    cin >> a[i];
    if (i != 0)
        st.insert(a[i] - a[i - 1]);
}
if (n == 2)
{
    cout << 1 << " " << a[1];
    return 0;
}
int raz = a[1] - a[0];
st.erase(st.find(raz));
int sol = 1e9;
int ind = -1;
int val = -1;
for (int i = 2; i < n; i++)
{
    int l = a[i - 1];
    int r = a[i];
    st.erase(st.find(r - l));
    st.insert((r - l) / 2 + (r - l) % 2);
    int cur = *st.rbegin();
    if (cur < sol)
    {
        sol = cur;
        ind = 1;
        val = l + (r - l) / 2;
    }
    st.erase(st.find((r - l) / 2 + (r - l) % 2));
    st.insert(r - l);
}
st.insert(raz);
st.erase(st.find(a[n - 1] - a[n - 2]));
for (int i = 1; i < n - 1; i++)
{
    int l = a[i - 1];
    int r = a[i];
    st.erase(st.find(r - l));
    st.insert((r - l) / 2 + (r - l) % 2);
    int cur = *st.rbegin();
    if (cur < sol)
    {
        sol = cur;
        ind = n;
        val = l + (r - l) / 2;
    }
    st.erase(st.find((r - l) / 2 + (r - l) % 2));
    st.insert(r - l);
}
cout << ind << " " << val;


}


