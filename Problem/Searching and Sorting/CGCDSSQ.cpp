//https://codeforces.com/contest/475/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, long long> ans;
    ans[a[0]]++;
    map<int, long long> last = ans;
    for (int i = 1; i < n; i++) {
        map<int, long long> mp;
        mp[a[i]]++, ans[a[i]]++;
        for (auto it = last.begin(); it != last.end(); ++it) {
            int x = __gcd(it->first, a[i]);
            mp[x] += it->second;
            ans[x] += it->second;
        }
        last = mp;
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }


    return 0;
}
