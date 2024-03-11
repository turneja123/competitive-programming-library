//https://dmoj.ca/problem/mathp7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int main() {
    IOS;
    long long n, ans = 0;
    cin >> n;
    long long x = sqrt(n);

    for (long long i = 1; i <= x; i++) {
        ans += n / i;
    }
    ans = 2 * ans - x * x;
    cout << ans << endl;

    return 0;
}
