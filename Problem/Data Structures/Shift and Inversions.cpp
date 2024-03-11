//solution for https://atcoder.jp/contests/abc190/tasks/abc190_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

int a[N];

tree <int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> t;

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        t.insert(a[i]);
        ans += t.size() - t.order_of_key(a[i] + 1);
    }
    for (int i = 0; i < n; i++) {
        cout << ans << endl;
        ans += t.size() - t.order_of_key(a[i] + 1);
        ans -= t.order_of_key(a[i]);
    }

    return 0;
}
