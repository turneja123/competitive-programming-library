//https://codeforces.com/contest/2053/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

long long ans = 0;

void calc(long long n, long long add, long long k, long long pw) {
    long long mid = n / 2;
    if (n < k) {
        return;
    }
    if (n % 2 == 1) {
        ans += pw * (mid + 1) + (pw / 2) * add;
    }
    add += mid + n % 2;
    calc(mid, add, k, pw * 2);
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        calc(n, 0, k, 1);
        cout << ans << endl;
        ans = 0;
    }
    return 0;
}
