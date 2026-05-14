//https://codeforces.com/contest/2070/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int n;
    cin >> n;
    string s;
    cin >> s;
    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> tr;
    tr.insert({0, 0});
    map<int, int> mp[4];
    mp[0][0]++;
    ll ans = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '0') {
            sum++;
        } else {
            sum -= 3;
        }
        ans += tr.order_of_key({sum - 2, INF});
        int m = (i % 4 - 3 + 4) % 4;
        ans += mp[m][sum + 1];

        tr.insert({sum, i});
        mp[i % 4][sum]++;
    }
    cout << ans;


    return 0;
}
