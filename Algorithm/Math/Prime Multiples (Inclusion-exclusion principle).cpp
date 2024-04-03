//https://cses.fi/problemset/task/2185/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 22;

long long a[K];

int main() {
    IOS;
    long long n; int k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int j = 1; j < (1 << k); j++) {
        long long sum = n;
        for (int i = 0; i < k; i++) {
            int c = j & (1 << i);
            if (c) {
                sum /= a[i];
            }
        }
        if (__builtin_popcount(j) % 2 == 1) {
            ans += sum;
        } else {
            ans -= sum;
        }
    }
    cout << ans;

    return 0;
}
