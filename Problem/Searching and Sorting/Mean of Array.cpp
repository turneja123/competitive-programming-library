//https://www.spoj.com/problems/MEANARR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

tree<pair<long long, int>, null_type, less<pair<long long, int>>, rb_tree_tag, tree_order_statistics_node_update> t;

int main() {
    IOS;
    int n; long long k, sum = 0, ans = 0;
    cin >> n >> k;
    t.insert(make_pair(0, 0));
    for (int i = 1; i <= n; i++) {
        long long a; cin >> a;
        a -= k;
        sum += a;
        ans += t.order_of_key(make_pair(sum, n + 1));
        t.insert(make_pair(sum, i));
    }
    cout << ans;

    return 0;
}
