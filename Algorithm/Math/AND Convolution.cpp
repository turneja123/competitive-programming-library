//https://judge.yosupo.jp/problem/bitwise_and_convolution
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const long long M = 998244353;
const int N = 2e6 + 5;

long long a[N];
long long b[N];
long long ans[N];

int main() {
    IOS;
    int n;
    cin >> n;
    int bits = 1 << n;
    for (int j = 0; j < bits; j++) {
        cin >> a[j];
    }
    for (int j = 0; j < bits; j++) {
        cin >> b[j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bits; j++) {
            int c = j & (1 << i);
            if (c) {
                a[j ^ (1 << i)] = (a[j ^ (1 << i)] + a[j]) % M;
                b[j ^ (1 << i)] = (b[j ^ (1 << i)] + b[j]) % M;
            }
        }
    }
    for (int j = 0; j < bits; j++) {
        ans[j] = a[j] % M * b[j] % M;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bits; j++) {
            int c = j & (1 << i);
            if (c) {
                ans[j ^ (1 << i)] = (ans[j ^ (1 << i)] - ans[j] + M) % M;
            }
        }
    }

    for (int j = 0; j < bits; j++) {
        cout << ans[j] % M << " ";
    }

    return 0;
}
