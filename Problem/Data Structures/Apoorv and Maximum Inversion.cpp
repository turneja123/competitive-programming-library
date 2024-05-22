//https://www.spoj.com/problems/SAS001/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

int a[N];
tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> t;

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long cur = 0, mx = 0; int ans = 0;
    for (int i = 0; i < k; i++) {
        cur += t.size() - t.order_of_key(make_pair(a[i], INF));
        t.insert(make_pair(a[i], i));
    }
    mx = cur;
    for (int i = k; i < n; i++) {
        cur -= t.order_of_key(make_pair(a[i - k], -1));
        t.erase(make_pair(a[i - k], i - k));
        cur += t.size() - t.order_of_key(make_pair(a[i], INF));
        t.insert(make_pair(a[i], i));
        if (cur > mx) {
            mx = cur;
            ans = i - k + 1;
        }
    }
    cout << ans + 1 << " " << mx;
    return 0;
}
