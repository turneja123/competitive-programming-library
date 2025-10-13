//https://qoj.ac/contest/2539/problem/14429
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    string s;
    cin >> s;
    int n = s.size();
    string ans = "";
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            ans += s[i];
        } else {
            ans += s[i];
            ans += s[i - 1];
        }
    }
    cout << ans;
    return 0;
}
