//https://codeforces.com/contest/1045/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n;
    cin >> n;
    map<int, int> mp;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int mask = 0;
        for (char c : s) {
            int p = c - 'a';
            mask ^= 1 << p;
        }
        for (int j = 0; j < 26; j++) {
            ans += mp[mask ^ (1 << j)];
        }
        ans += mp[mask];

        mp[mask]++;
    }
    cout << ans;
    return 0;
}
