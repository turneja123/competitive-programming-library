//https://codeforces.com/contest/2109/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int calc(int a, int b) {
    int ans = 0;
    while (a > 1) {
        a = (a + 1) / 2;
        ans++;
    }
    while (b > 1) {
        b = (b + 1) / 2;
        ans++;
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        cout << 1 + min(calc(min(x, n - x + 1), m), calc(n, min(y, m - y + 1))) << endl;
    }
    return 0;
}
