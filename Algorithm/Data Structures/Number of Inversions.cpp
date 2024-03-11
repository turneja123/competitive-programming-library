//solution for https://www.codechef.com/LRNDSA04/problems/EURON
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

tree <pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        t.insert({a, i});
        ans += t.size() - t.order_of_key({a, INF});
    }
    cout << ans;
    return 0;
}
