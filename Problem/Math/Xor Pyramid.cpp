//https://cses.fi/problemset/task/2419/
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
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        int x = n - 1, y = i, z = x | y;
        if (z == x) {
            ans ^= a;
        }
    }
    cout << ans;

    return 0;
}
