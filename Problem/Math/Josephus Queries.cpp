//https://cses.fi/problemset/task/2164/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

long long calc(long long n, long long k) {
    if (n == 1) {
        return 1;
    }
    if (k <= (n + 1) / 2) {
        long long ans = 2 * k;
        if (ans > n) {
            ans %= n;
        }
        return ans;
    }
    long long ans = calc(n / 2, k - (n + 1) / 2);
    return 2 * ans + ((n % 2) ? 1 : -1);
}

int main() {
    IOS;
    int q;
    cin >> q;
    while (q--) {
        long long n, k;
        cin >> n >> k;
        cout << calc(n, k) << endl;
    }
    return 0;
}
