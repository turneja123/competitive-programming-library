//https://atcoder.jp/contests/abc389/tasks/abc389_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int r;
    cin >> r;
    long long ans = 0;
    for (int i = 1; i <= r; i++) {
        long double b = sqrtl((long double)r * r - (long double)((long double)i - 0.5) * (long double)((long double)i - 0.5));
        ans += (long long)floorl(b - 0.5) * 4;
    }
    cout << ans + 1;
    return 0;
}
