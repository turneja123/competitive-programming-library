//https://codeforces.com/contest/1398/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int sum = 0;
        string s;
        cin >> s;
        map<int, int> mp;
        mp[1]++;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            sum += s[i] - '0';
            ans += mp[sum - i];
            mp[sum - i]++;
        }
        cout << ans << endl;
    }
    return 0;
}
