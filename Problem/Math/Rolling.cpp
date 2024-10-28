//https://tlx.toki.id/contests/troc-39/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long M = 998244353;

long long a[N];
long long fact[N];

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % M;
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    long long ans = 0, inv = modPow(2, M - 2);
    for (int i = 0; i < n; i++) {
        ans += (sum - a[i]) % M * a[i] % M * (a[i] - 1) % M * inv % M;
    }
    ans %= M;
    ans = ans * fact[n] % M * inv % M;
    cout << ans;


    return 0;
}
